#include "Server.hpp"

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#include "Logger.hpp"
#include "SocketMonitor.hpp"

Server::~Server()
{
    SocketMonitor::get().stopMonitor(serverFd);
    close(serverFd);
}

void Server::init(uint16_t port)
{
    LOG_DEBUG() << "Initializing server using port: " << port;
    sockaddr_in server_addr{};

    serverFd = socket(AF_INET, SOCK_STREAM, 0);
    if (serverFd == -1)
    {
        LOG_ERROR() << "Failed to create server socket! errno = " << errno;
        exit(-1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port);

    if (bind(serverFd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        close(serverFd);
        LOG_ERROR() << "Failed to bind server! errno = " << errno;
        exit(-1);
    }

    if (listen(serverFd, 10) < 0)
    {
        close(serverFd);
        LOG_ERROR() << "Failed to listen server! errno = " << errno;
        exit(-1);
    }

    SocketMonitor::get().startMonitor(MonitorInfo{serverFd, Endpoint{0}, true, false});
}