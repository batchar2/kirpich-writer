#pragma once

#include <thread>
#include <memory>

#include <httplib/httplib.h>
#include <config/environment.h>


namespace k::http {

    class server
    {
    private:
        int port_;
        std::thread th_;
        bool is_running_;
        std::shared_ptr<httplib::Server> server_;
    public:
        static server* instance() {
            static server inst(k::config::environment::instance()->HTTP_SERVER_PORT());
            return &inst;
        }
        inline bool is_running() const {
            return this->is_running_;
        }
        inline bool stop() {
            if (this->is_running_) {
                this->server_->stop();
                if (this->th_.joinable()) {
                    this->th_.join();
                }
            }
            return !this->is_running_;
        }
    private:
        server(int port);
    private:
        void run();
    };
}

