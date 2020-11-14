cmake_minimum_required(VERSION 3.0)
project(kirpich_writer)

add_executable(kirpich_writer
        main.cpp
        http/server.cpp http/server.h
        archiving/manager.cpp archiving/manager.h
        task/base_task.h
        archiving/ffmpeg/camera.cpp archiving/ffmpeg/camera.h
)


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
)


#target_link_libraries(kirpich_writer
#        ${AVCODEC_LIBRARY}
#        ${AVFORMAT_LIBRARY}
#        ${AVUTIL_LIBRARY}
#        ${AVFILTER_LIBRARY}
#        ${SWSCALE_LIBRARY}
#        pthread
#)

install(TARGETS kirpich_writer DESTINATION ${CMAKE_INSTALL_PREFIX})