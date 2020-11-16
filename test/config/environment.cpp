#define BOOST_TEST_MODULE environment

#include <boost/test/unit_test.hpp>

#include "config/environment.h"


BOOST_AUTO_TEST_CASE(values)
{
    ::setenv("HTTP_SERVER_PORT","5001",1);
    ::setenv("LOG_PATH","/LOG_PATH",1);
    ::setenv("ARCHIVE_DURATION_SEC","1",1);

    auto conf = k::config::environment::instance();

    BOOST_CHECK_EQUAL(conf->HTTP_SERVER_PORT(), 5001);
    BOOST_CHECK_EQUAL(conf->LOG_PATH(), "/LOG_PATH");
    BOOST_CHECK_EQUAL(conf->ARCHIVE_DURATION_SEC(), 1);
}