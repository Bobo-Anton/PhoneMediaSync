#include "SocketMonitor.hpp"

#include <sys/epoll.h>
#include <unistd.h>

#include "Logger.hpp"

SocketMonitor::SocketMonitor()
{
    pollFd = epoll_create1(0);
    if (pollFd == -1)
    {
        LOG_ERROR() << "Filed to create epoll. errno = " << errno;
        exit(-1);
    }
}

SocketMonitor::~SocketMonitor() { close(pollFd); }

SocketMonitor& SocketMonitor::get()
{
    static SocketMonitor instance;
    return instance;
}

void SocketMonitor::startMonitor(const MonitorInfo& monitorInfo)
{
    epoll_event event;
    event.data.u64 = monitorInfo.endpoint.fullEndpoint;
    event.events = EPOLLRDHUP | EPOLLHUP | EPOLLONESHOT;
    if (monitorInfo.monitorReads)
    {
        event.events |= EPOLLIN;
    }
    if (monitorInfo.monitorWrites)
    {
        event.events |= EPOLLOUT;
    }
    int res = epoll_ctl(pollFd, EPOLL_CTL_ADD, monitorInfo.fd, &event);
    if (res == -1)
    {
        LOG_WARN() << "Failed to add to monitoring. fd = " << monitorInfo.fd << " errno = " << errno;
    }
    else
    {
        LOG_DEBUG() << "Fd added to monitoring. fd = " << monitorInfo.fd;
    }
}

void SocketMonitor::stopMonitor(int fd)
{
    int res = epoll_ctl(pollFd, EPOLL_CTL_DEL, fd, nullptr);
    if (res == -1)
    {
        LOG_WARN() << "Failed to remove from monitoring. fd = " << fd << " errno = " << errno;
    }
}