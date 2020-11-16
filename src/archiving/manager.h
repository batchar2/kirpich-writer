#pragma once

#include <map>
#include <mutex>
#include <thread>
#include <string>

#include "ffmpeg/camera.h"

namespace k::archiving {

    class manager
    {
    private:
        std::thread th_;
        mutable bool close_;
        mutable bool is_running_;
    private:
        std::mutex mtx_;
        std::map<std::string, ffmpeg::camera_ptr> cameras_;
    public:
        static manager* instance() {
            static manager inst;
            return &inst;
        }
        inline bool is_running() const {
            return this->is_running_;
        }
        inline bool stop() {
            if (this->is_running_) {
                this->close_ = false;
                this->stop_all();

                if (this->th_.joinable()) {
                    this->th_.join();
                }
            }
            return !this->is_running_;
        }
    public:
        bool camera_stop(const std::string &camid);
        bool camera_pause(const std::string &camid);
        bool camera_start(const std::string &camid, const std::string &rtsp_uri);
    private:
        void stop_all();
    private:
        manager();
    private:
        void run();
    };
}

