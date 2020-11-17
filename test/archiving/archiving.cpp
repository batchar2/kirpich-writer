#define BOOST_TEST_MODULE archiving

#include <thread>
#include <filesystem>

#include <boost/test/unit_test.hpp>

#include "archiving/manager.h"


BOOST_AUTO_TEST_CASE(start_stop_manager)
{
   auto manager = k::archiving::manager::instance();

   std::this_thread::sleep_for(std::chrono::seconds(1));

   BOOST_CHECK_EQUAL(manager->is_running(), true);

   manager->stop();

   BOOST_CHECK_EQUAL(manager->is_running(), false);
}


BOOST_AUTO_TEST_CASE(start_camera)
{
   ::setenv("ARCHIVE_DURATION_SEC","2",1);

   auto manager = k::archiving::manager::instance();

   std::this_thread::sleep_for(std::chrono::seconds(1));

   BOOST_CHECK_EQUAL(manager->is_running(), true);

   manager->camera_start("1", "rtsp://stream.studio360.tv:554/nw/nw_576p");

   std::this_thread::sleep_for(std::chrono::seconds(3));

   BOOST_CHECK_EQUAL((std::filesystem::exists("camera-1.csv")), true);

   manager->stop();

   BOOST_CHECK_EQUAL(manager->is_running(), false);
}
