#pragma once

#include <string>
#include <memory>

//#include <core/posix/fork.h>
//#include <core/posix/process.h>
//#include <core/posix/signal.h>


//#include <boost/process.hpp>

namespace k::archiving::ffmpeg {

//    namespace bp = boost::process;

    class camera
    {
    private:
//        std::shared_ptr<posix::ChildProcess> process_;
//        bp::ipstream pipe_;
    private:
        std::string camid_;
        std::string rtsp_uri_;
    public:
        camera(const std::string &camid, const std::string &rtsp_uri);
    public:
//        inline bp::ipstream& pipe() {
//            return this->pipe_;
//        }
    };

    typedef std::shared_ptr<camera> camera_ptr;
}

