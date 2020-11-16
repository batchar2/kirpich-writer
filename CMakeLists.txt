cmake_minimum_required(VERSION 3.0)
project(kirpich_writer)

set(CMAKE_CXX_STANDARD 17)

find_library(AVCODEC_LIBRARY avcodec)
find_library(AVFORMAT_LIBRARY avformat)
find_library(AVUTIL_LIBRARY avutil)
find_library(AVFILTER_LIBRARY avfilter)
find_library(SWRESAMPLE_LIBRARY swresample)
find_library(SWSCALE_LIBRARY swscale)



find_package(
        Boost
        CONFIG REQUIRED
        program_options
        thread
        log
        log_setup
        filesystem
)


file(GLOB_RECURSE SRC_FILES
        src/http/*.cpp
        src/config/*.cpp
        src/archiving/*.cpp
        src/archiving/ffmpeg*.cpp
        src/task/*.cpp
)



include_directories(src/)
include_directories(libs/)

add_definitions(-DCPPHTTPLIB_USE_POLL)
add_definitions(-DFMT_HEADER_ONLY)

set(JSON_BuildTests "OFF" CACHE BOOL "Disable json tests" FORCE)
include_directories(libs/json/include)

include_directories(libs/fmt/include)


set(BUILD_TESTING "FALSE")
add_subdirectory(libs/process)








enable_testing()

add_subdirectory(src)
add_subdirectory(test)
