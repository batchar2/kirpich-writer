cmake_minimum_required(VERSION 3.0)
project(kirpich_writer)

set(CMAKE_CXX_STANDARD 20)

find_library(AVCODEC_LIBRARY avcodec)
find_library(AVFORMAT_LIBRARY avformat)
find_library(AVUTIL_LIBRARY avutil)
find_library(AVFILTER_LIBRARY avfilter)
find_library(SWRESAMPLE_LIBRARY swresample)
find_library(SWSCALE_LIBRARY swscale)


file(GLOB_RECURSE SRC_FILES
        src/http/*.cpp
        src/archiving/*.cpp
        src/archiving/ffmpeg*.cpp
        src/task/*.cpp
)



include_directories(src/)
include_directories(libs/)




enable_testing()

add_subdirectory(src)
add_subdirectory(test)
