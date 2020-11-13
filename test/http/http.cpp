#define BOOST_TEST_MODULE http

#include <thread>
#include <boost/test/unit_test.hpp>

#include "http/server.h"



BOOST_AUTO_TEST_CASE(start_stop)
{
    auto http_server = k::http::server::instance();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    BOOST_CHECK_EQUAL(http_server->is_running(), true);

    http_server->stop();

    BOOST_CHECK_EQUAL(http_server->is_running(), false);
}
