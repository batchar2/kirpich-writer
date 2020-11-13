#define BOOST_TEST_MODULE archiving

#include <thread>
#include <boost/test/unit_test.hpp>

#include "archiving/manager.h"


BOOST_AUTO_TEST_CASE(start_stop)
{
    auto manager = k::archiving::manager::instance();

    std::this_thread::sleep_for(std::chrono::seconds(1));

    BOOST_CHECK_EQUAL(manager->is_running(), true);

    manager->stop();

    BOOST_CHECK_EQUAL(manager->is_running(), false);
}
