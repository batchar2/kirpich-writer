#include "manager.h"

using namespace k::archiving;


manager::manager()
    : is_running_(false)
{
    std::thread th(&manager::run, this);
    this->th_ = std::move(th);
}


void manager::run()
{
    this->is_running_ = true;
    while (this->is_running_) {
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    this->is_running_ = false;
}


bool manager::camera_stop(const std::string &camid)
{
    std::lock_guard<std::mutex> lock(this->mtx_);

    return true;
}


bool manager::camera_pause(const std::string &camid)
{
    std::lock_guard<std::mutex> lock(this->mtx_);

    return true;
}


bool manager::camera_start(const std::string &camid, const std::string &rtsp_uri)
{
    std::lock_guard<std::mutex> lock(this->mtx_);

//    if (!this->cameras_.contains(camid)) {
//        auto camera = std::make_shared<ffmpeg::camera>(camid, rtsp_uri);
//        this->cameras_[camid] = camera;
//        return true;
//    }

    return false;
}