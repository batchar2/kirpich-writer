#include <iostream>
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
    signal(SIGCHLD, SIG_IGN); /* Silently (and portably) reap children. */

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

    k::archiving::ffmpeg::camera cam(camid, rtsp_uri);

//
//    cam.process()->

//
//
//
//    std::this_thread::sleep_for(std::chrono::milliseconds(300));
//
//    cam.process()->try_get_exit_status(exit_status);
//    std::cerr << "2 exit_status>" << exit_status << std::endl;

    if (this->cameras_.find(camid) == this->cameras_.end()) { // if (!this->cameras_.contains(camid)) {
        auto camera = std::make_shared<ffmpeg::camera>(camid, rtsp_uri);
        this->cameras_[camid] = camera;

        int exit_status = 128;
        cam.process()->try_get_exit_status(exit_status);

        return true;
    }


    return false;
}