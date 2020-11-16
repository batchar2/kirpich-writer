#pragma once

#include <string>

namespace k::config {

    class environment
    {
    private:
        int HTTP_SERVER_PORT_;
        std::string LOG_PATH_;
        int ARCHIVE_DURATION_SEC_;
    public:
        static environment* instance() {
            static environment inst;
            return &inst;
        }
    public:
        inline int HTTP_SERVER_PORT() const {
            return this->HTTP_SERVER_PORT_;
        }
        inline const std::string& LOG_PATH() const {
            return this->LOG_PATH_;
        }
        inline const int ARCHIVE_DURATION_SEC() const {
            return this->ARCHIVE_DURATION_SEC_;
        }
    private:
        inline std::string get_env_value(const std::string &var_name, std::string default_value) {
            std::string value = default_value;
            const char* env_value = std::getenv(var_name.c_str());
            if (env_value != nullptr) {
                value = env_value;
            }
            return value;
        }

        inline int get_env_value_int(const std::string &var_name, int default_value) {
            std::string value = this->get_env_value(var_name, std::to_string(default_value));
            return std::stoi(value);
        }

    private:
        environment();
    };

}

