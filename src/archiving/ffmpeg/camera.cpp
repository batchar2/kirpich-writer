#include "camera.h"

using namespace k::archiving::ffmpeg;

camera::camera(const std::string &camid, const std::string &rtsp_uri)
    :
        camid_(camid),
        rtsp_uri_(rtsp_uri)
{

}