#include <iostream>

#include "http/server.h"
#include "archiving/manager.h"

static bool is_running = true;

static void handler(int sig)
{
    if (sig == SIGCHLD) {
        pid_t pid = wait(NULL);
        // printf("Pid %d exited.\n", pid);
    } else {
        ::is_running = false;
    }
}


int main()
{
    std::signal(SIGCHLD, handler);
    std::signal(SIGINT, handler);
    std::signal(SIGTERM, handler);

    auto http_server = k::http::server::instance();
    auto archiving_manager = k::archiving::manager::instance();

//    archiving_manager->camera_start("1", "rtsp://stream.studio360.tv:554/nw/nw_576p");

    while (::is_running) { // просто ждем пока сервер работает, заменить на сигнал или кондвар
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }

    http_server->stop();
    archiving_manager->stop();

    return 0;
}
