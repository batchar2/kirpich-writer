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
    this->is_running_ = true;
    while (this->is_running_) { // тут будет еще управление процессами
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    this->is_running_ = false;
}


bool manager::camera_stop(const std::string &camid)
{
    std::lock_guard<std::mutex> lock(this->mtx_);
    if (this->cameras_.find(camid) != this->cameras_.end()) {
        this->cameras_[camid]->stop();
        this->cameras_.erase(camid);
        return true;
    }
    return false;
}


bool manager::camera_pause(const std::string &camid)
{
    std::lock_guard<std::mutex> lock(this->mtx_);
    if (this->cameras_.find(camid) != this->cameras_.end()) {
        this->cameras_[camid]->pause();
        this->cameras_.erase(camid);
        return true;
    }
    return true;
}


bool manager::camera_start(const std::string &camid, const std::string &rtsp_uri)
{
    std::lock_guard<std::mutex> lock(this->mtx_);
    if (this->cameras_.find(camid) == this->cameras_.end()) { // if (!this->cameras_.contains(camid)) {
        this->cameras_[camid] = std::make_shared<ffmpeg::camera>(camid, rtsp_uri);
        return true;
    }
    return false;
}


void manager::stop_all() {
    std::lock_guard<std::mutex> lock(this->mtx_);
    for (auto &cam : this->cameras_) {
        cam.second->stop();
    }
}