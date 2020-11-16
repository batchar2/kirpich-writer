#pragma once

#include <memory>

#include "boost/log/trivial.hpp"
#include "boost/log/utility/setup.hpp"

#include "config/environment.h"

namespace k::logger {


    inline void init()
    {
        //: (%LineID%) [%ProcessID%:%ThreadID%]
        static const std::string COMMON_FMT("[%TimeStamp%] %Message%");

        boost::log::add_console_log(
                std::cerr,
                boost::log::keywords::format = COMMON_FMT,
                boost::log::keywords::auto_flush = true
        );
        boost::log::add_file_log (
                // boost::log::keywords::file_name = k::config::environment::instance()->LOG_PATH() + "/vin-server%3N.log",
                boost::log::keywords::rotation_size = 1 * 1024 * 1024,
                boost::log::keywords::max_size = 20 * 1024 * 1024,
                boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
                boost::log::keywords::format = COMMON_FMT,
                boost::log::keywords::auto_flush = true
        );

        boost::log::add_common_attributes();
    }


#define _FMT            "[" << __FILE__ << ":" << __LINE__ << "] "

#define LOG_TRACE       BOOST_LOG_TRIVIAL(trace)   << " [trace] "   << _FMT
#define LOG_DEBUG       BOOST_LOG_TRIVIAL(debug)   << " [debug] "   << _FMT
#define LOG_INFO        BOOST_LOG_TRIVIAL(info)    << " [info] "    << _FMT
#define LOG_WARNING     BOOST_LOG_TRIVIAL(warning) << " [warning] " << _FMT
#define LOG_ERROR       BOOST_LOG_TRIVIAL(error)   << " [error] "   << _FMT
#define LOG_FATAL       BOOST_LOG_TRIVIAL(fatal)   << " [fatal] "   << _FMT
}
