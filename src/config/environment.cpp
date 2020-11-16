#include <sstream>
#include <iostream>

#include "environment.h"

using namespace k::config;

environment::environment()
{
    this->LOG_PATH_ = this->get_env_value("LOG_PATH", "/log");
    this->HTTP_SERVER_PORT_ = this->get_env_value_int("HTTP_SERVER_PORT", 5000);

    std::stringstream ss;

    ss << "CONFIGURATION:" << std::endl;
    ss << "LOG_PATH:          " << this->LOG_PATH_ << std::endl;
    ss << "HTTP_SERVER_PORT:  " << this->HTTP_SERVER_PORT_ << std::endl;

    ss << std::endl << std::endl;

    std::cerr << ss.str();
}