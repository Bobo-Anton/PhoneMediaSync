#include <signal.h>

#include <semaphore>

#include "Logger.hpp"
#include "Server.hpp"
#include "SocketMonitor.hpp"

std::binary_semaphore wait_sem(0);

void signal_handler(int) { wait_sem.release(); }

int main()
{
    LOG_DEBUG() << "Server Application start!";

    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);

    // Initialize socket monitor
    static_cast<void>(SocketMonitor::get());

    Server srv;
    srv.init(10000);

    wait_sem.acquire();

    LOG_DEBUG() << "Server Application end!";
    return 0;
}