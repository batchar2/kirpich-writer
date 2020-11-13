#include <iostream>

#include "http/server.h"
#include "archiving/manager.h"

static bool is_running = true;

int main()
{
    auto http_server = k::http::server::instance();
    auto archiving_manager = k::archiving::manager::instance();
    
    while (is_running) { // просто ждем пока сервер работает, заменить на сигнал или кондвар
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    http_server->stop();
    archiving_manager->stop();

    return 0;
}
