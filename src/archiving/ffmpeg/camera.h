#pragma once

#include <string>
#include <memory>


namespace k::archiving::ffmpeg {

    class camera
    {
    private:
        std::string camid_;
        std::string rtsp_uri_;
    public:
        camera(const std::string &camid, const std::string &rtsp_uri);
    };

    typedef std::shared_ptr<camera> camera_ptr;
}

