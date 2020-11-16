#include <iostream>

#include "log/log.h"
#include "http/server.h"
#include "archiving/manager.h"
#include "config/environment.h"

static bool is_running = true;

static void handler(int sig)
{
    if (sig == SIGCHLD) {
        pid_t pid = wait(nullptr);
        std::cerr << "Pid " << pid <<  " exited" << std::endl;
    } else {
        ::is_running = false;
    }
}


int main()
{
    std::signal(SIGCHLD, handler);
    std::signal(SIGINT,  handler);
    std::signal(SIGTERM, handler);

    k::logger::init();

    auto config = k::config::environment::instance();
    auto http_server = k::http::server::instance();
    auto archiving_manager = k::archiving::manager::instance();

    while (::is_running) { // просто ждем пока сервер работает, заменить на сигнал или кондвар
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    (void)config;
    http_server->stop();
    archiving_manager->stop();

    return 0;
}
