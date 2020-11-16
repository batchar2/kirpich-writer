#include <iostream>
#include <fstream>
#include <csignal>

#include <fmt/format.h>
#include <config/environment.h>

extern "C" {
#include <libavutil/opt.h>
#include <libavcodec/avcodec.h>
#include <libavutil/channel_layout.h>
#include <libavutil/common.h>
#include <libavutil/imgutils.h>
#include <libavutil/mathematics.h>
#include <libavutil/samplefmt.h>
#include <libswscale/swscale.h>
#include <libavformat/avformat.h>
#include <libavutil/time.h>
#include <libavutil/log.h>
}



#include "camera.h"




static char error_buf[1024] = {0};
#define GET_AV_ERROR(r) (av_strerror(r, ::error_buf, sizeof(error_buf)), error_buf)

static AVFormatContext* create_output_fmt(const AVFormatContext *ifmt_ctx, const std::string &camid);


static void handler(int sig)
{
    ::exit(0);
}

using namespace k::archiving::ffmpeg;


camera::camera(const std::string &camid, const std::string &rtsp_uri)
    :
        camid_(camid),
        rtsp_uri_(rtsp_uri)
{
    this->process_ = std::make_shared<process::Process>([&] {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        int ret_code = this->start();
        ::exit(ret_code);
    });
}


void camera::stop()
{
    // rm all data
    //
    //
    this->process_->signal(SIGINT);
}


void camera::pause()
{
    this->process_->signal(SIGINT);
}


int camera::start()
{
    std::signal(SIGINT, handler);
    std::signal(SIGTERM, handler);

    int ret = 0;
    AVStream *stream_video = nullptr, *stream_audio = nullptr;
    int stream_video_id = -1, stream_audio_id = -1;

//    ::av_register_all();
    ::avformat_network_init();

    AVFormatContext* ifmt_ctx = nullptr;
    if(::avformat_open_input(&ifmt_ctx, this->rtsp_uri_.c_str(), nullptr, nullptr) != 0){
        std::cerr << GET_AV_ERROR(ret) << std::endl;
        return ret;
    }

    ::av_opt_set_int(ifmt_ctx, "probesize", INT_MAX, 0);
    ::av_opt_set_int(ifmt_ctx, "analyzeduration", INT_MAX, 0);

    if (avformat_find_stream_info(ifmt_ctx,  nullptr) < 0) {
        std::cerr << GET_AV_ERROR(ret) << std::endl;
        return ret;
    }

    // output configure
    AVFormatContext* ofmt_ctx = ::create_output_fmt(ifmt_ctx, this->camid_);
    if (ofmt_ctx) {
        AVPacket pkt;
        while (true) {
            av_init_packet(&pkt);
            if (av_read_frame(ifmt_ctx, &pkt) < 0) {
                break;
            }
            av_interleaved_write_frame(ofmt_ctx, &pkt);
            av_packet_unref(&pkt);
        }
        return 0;
    }
    return -1;
}


static AVFormatContext* create_output_fmt(const AVFormatContext* ifmt_ctx, const std::string &camid)
{
    int ret = 0;
    int stream_index = -1;
    AVFormatContext *ofmt_ctx = nullptr;

    std::string url_tmpl = R"(archive-camera-{id}-%Y-%m-%d.%H-%M-%S.mp4)";
    std::string segment_list_tmpl = R"(camera-{id}.csv)";

    std::string url = fmt::format(url_tmpl, fmt::arg("id", camid));
    std::string segment_list = fmt::format(segment_list_tmpl, fmt::arg("id", camid));


    if (::avformat_alloc_output_context2(&ofmt_ctx, nullptr, "segment",  url.c_str()) != 0) {
        std::cerr << "avformat_alloc_output_context2 failed" << std::endl;
        return nullptr;
    }

    if((ret = avio_open2(&ofmt_ctx->pb, url.c_str(), AVIO_FLAG_WRITE, &ofmt_ctx->interrupt_callback, nullptr)) < 0) { //    if (avio_open(&ofmt_ctx->pb, url, AVIO_FLAG_WRITE) != 0) {
        std::cerr << GET_AV_ERROR(ret) << std::endl;
        return nullptr;
    }
    for (int i = 0; i < ifmt_ctx->nb_streams; i++) {
        AVStream *st = nullptr;
        if (!(st = avformat_new_stream(ofmt_ctx, nullptr))) {
            std::cerr << "ERROR" << std::endl;
            return nullptr;
        }
        AVCodecParameters *ipar = ifmt_ctx->streams[i]->codecpar;
        AVCodecParameters *opar = st->codecpar;
        avcodec_parameters_copy(opar, ipar);

        if (!ofmt_ctx->oformat->codec_tag ||
            av_codec_get_id (ofmt_ctx->oformat->codec_tag, ipar->codec_tag) == opar->codec_id ||
            av_codec_get_tag(ofmt_ctx->oformat->codec_tag, ipar->codec_id) <= 0)
        {
            opar->codec_tag = ipar->codec_tag;
        } else {
            opar->codec_tag = 0;
        }
        st->sample_aspect_ratio = ifmt_ctx->streams[i]->sample_aspect_ratio;
        st->time_base = ifmt_ctx->streams[i]->time_base;
        av_dict_copy(&st->metadata, ifmt_ctx->streams[i]->metadata, 0);
    }

    AVDictionary *opts = nullptr;

    av_dict_set(&opts, "increment_tc","0",0); // если 1 то время начала будет в первом сегменте, что не допустимо
    av_dict_set(&opts, "segment_format","mp4",0); // пишем в чанки h264

    av_dict_set(&opts, "segment_list", segment_list.c_str(),0);
    av_dict_set(&opts, "segment_list_type","csv",0); // ведем список сегментов
    av_dict_set(&opts, "segment_list_flags","cache",0); // параметры сегмента


    std::string segment_time = std::to_string(k::config::environment::instance()->ARCHIVE_DURATION_SEC());
    av_dict_set(&opts, "segment_time",segment_time.c_str(),0);  // длина сегмента
    av_dict_set(&opts, "strftime","1",0); // новые сегменты разрешены и начинаются с даты-время

    av_dict_set(&opts, "segment_atclocktime","1",0); // деление выполняется через равные интервалы времени, начиная с 00:00
    av_dict_set(&opts, "reset_timestamps","1",0);

    if ((ret = avformat_write_header(ofmt_ctx, &opts) < 0)) {
        std::cerr << GET_AV_ERROR(ret) << std::endl;
        return nullptr;
    }

    av_dict_free(&opts);


    return ofmt_ctx;
}

