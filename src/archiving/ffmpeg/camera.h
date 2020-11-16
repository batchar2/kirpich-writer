#pragma once

#include <string>
#include <memory>

//#include <core/posix/fork.h>
//#include <core/posix/process.h>
//#include <core/posix/signal.h>


#include <process/process.hpp>

namespace k::archiving::ffmpeg {

    namespace process = TinyProcessLib;

    typedef std::shared_ptr<process::Process> process_ptr;

    class camera
    {
    private:
        process_ptr process_;
    private:
        std::string camid_;
        std::string rtsp_uri_;
    public:
        camera(const std::string &camid, const std::string &rtsp_uri);
    public:
        inline process_ptr& process() {
            return this->process_;
        }
        void stop();
        void pause();
    private:
        int start();
    };

    typedef std::shared_ptr<camera> camera_ptr;
}

