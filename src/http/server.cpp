#include "server.h"

using namespace k::http;

server::server(int port)
    : port_(port), is_running_(false)
{
    std::thread th(&server::run, this);
    this->th_ = std::move(th);
}

void server::run()
{
    this->is_running_ = true;
    this->server_ = std::make_shared<httplib::Server>();


    this->server_->Post("/api/camera/start/", [&](const auto& req, auto& res) {

    });

    this->server_->set_keep_alive_max_count(30); // default 5
    this->server_->set_payload_max_length(1024 * 1024 * 1); // 1MB
    this->server_->set_read_timeout(10, 0); // 12 seconds
    this->server_->set_write_timeout(10, 0); // 12 seconds
    this->server_->listen("0.0.0.0", this->port_);

    this->is_running_ = false;
}
