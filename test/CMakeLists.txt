cmake_minimum_required(VERSION 3.0)
project(test)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

ADD_DEFINITIONS(-DBOOST_TEST_DYN_LINK)

include_directories("../src/")

set(UNIT_TESTS_INCLUDES ${PROJECT_INCLUDE_DIR}
        ${PROJECT_SOURCE_DIR}/src
        ${Boost_INCLUDE_DIR})


function(create_test test_name test_file_name)
    add_executable (${test_name} ${test_file_name} ${SRC_FILES})
    target_link_libraries(${test_name} ${AVCODEC_LIBRARY} ${AVFORMAT_LIBRARY} ${AVUTIL_LIBRARY} ${AVFILTER_LIBRARY} ${SWSCALE_LIBRARY} pthread ${Boost_LIBRARIES} tiny-process-library )#-nostartfiles -g)
    add_test (NAME ${test_name} COMMAND ${test_name})
endfunction()





create_test(http http/http.cpp)
create_test(archiving archiving/archiving.cpp)

