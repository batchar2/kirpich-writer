cmake_minimum_required(VERSION 3.0)
project(kirpich_writer)

add_executable(kirpich_writer
        main.cpp
        http/server.cpp http/server.h
        archiving/manager.cpp archiving/manager.h
        archiving/ffmpeg/camera.cpp archiving/ffmpeg/camera.h
        log/log.h config/environment.cpp config/environment.h)

target_link_libraries(
        ${PROJECT_NAME}
        Boost::program_options
        Boost::thread
        Boost::log
        Boost::log_setup
        Boost::filesystem

        ${AVCODEC_LIBRARY}
        ${AVFORMAT_LIBRARY}
        ${AVUTIL_LIBRARY}
        ${AVFILTER_LIBRARY}
        ${SWSCALE_LIBRARY}

        tiny-process-library
)

install(TARGETS kirpich_writer DESTINATION ${CMAKE_INSTALL_PREFIX})