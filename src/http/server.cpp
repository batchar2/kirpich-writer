#include "server.h"

#include <nlohmann/json.hpp>

#include "log/log.h"
#include "archiving/manager.h"


#define HTTP_STATUS_OK              (200)
#define HTTP_STATUS_404             (404)
#define HTTP_STATUS_BAD_REQUEST     (400)
#define HTTP_STATUS_ERROR           (500)

#define JSON_RPC_METHOD_START       ("start")
#define JSON_RPC_METHOD_PAUSE       ("start")
#define JSON_RPC_METHOD_STOP        ("stop")

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

    this->server_->Post("/api/json-rpc/", [&](const auto& req, auto& res) {
        std::vector<std::string> methods{JSON_RPC_METHOD_START, JSON_RPC_METHOD_PAUSE, JSON_RPC_METHOD_STOP};
        try {
            bool status = false;
            nlohmann::json r = nlohmann::json::parse(req.body);
            if (r.find("method") != r.end()
                && std::find(methods.begin(), methods.end(), r["method"]) != methods.end()
                && r.find("params") != r.end()
            ) {
                auto p = r["params"];
                if (r["method"] == JSON_RPC_METHOD_START && p.find("id") != p.end() && p.find("rtsp_uri")  != p.end()) {
                    status = k::archiving::manager::instance()->camera_start(p["id"], p["rtsp_uri"]);
                } else if (r["method"] == JSON_RPC_METHOD_PAUSE && p.find("id") != p.end()) {
                    status = k::archiving::manager::instance()->camera_pause(p["id"]);
                    if (!status) res.status = HTTP_STATUS_404;
                } else if (r["method"] == JSON_RPC_METHOD_STOP  && p.find("id") != p.end()) {
                    status = k::archiving::manager::instance()->camera_stop(p["id"]);
                    if (!status) res.status = HTTP_STATUS_404;
                } else {
                    res.status = HTTP_STATUS_BAD_REQUEST;
                }
                nlohmann::json json_response = {{"status", status},};
                res.set_content(json_response.dump(), "application/json");
                if (status) res.status = HTTP_STATUS_OK;
            }
        } catch (...) {
            res.status = HTTP_STATUS_ERROR;
            return;
        }
    });


    this->server_->set_logger([](const auto& req, const auto& res) {
        if (!req.method.empty()) {
            LOG_INFO << ">>> " << req.method << " " << req.path << "  " << res.status << std::endl;
        }
    });

    this->server_->set_keep_alive_max_count(30); // default 5
    this->server_->set_payload_max_length(1024 * 1024 * 1); // 1MB
    this->server_->set_read_timeout(12, 0); // 12 seconds
    this->server_->set_write_timeout(12, 0); // 12 seconds
    this->server_->listen("0.0.0.0", this->port_);

    this->is_running_ = false;
}
