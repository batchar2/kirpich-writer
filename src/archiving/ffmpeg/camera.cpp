#include <iostream>
#include <zconf.h>

#include "camera.h"

using namespace k::archiving::ffmpeg;

camera::camera(const std::string &camid, const std::string &rtsp_uri)
    :
        camid_(camid),
        rtsp_uri_(rtsp_uri)
{
    this->process_ = std::make_shared<process::Process>([&] {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
//        std::cerr << "+ 1 !!!!>>>>>" << std::endl;
        std::cout << this->run();// << "  " << ::getpid();
    });
}


std::string camera::run()
{
    // ffmpeg -i /home/bat/Video/2019_09_03_124721.mp4 -c copy -f segment -strftime 1 -segment_time 10 -segment_format mp4 out%Y-%m-%d_%H-%M-%S.mp4
    return "Hello world";
}