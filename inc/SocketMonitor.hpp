#pragma once

#include "Types.hpp"

struct MonitorInfo
{
    int fd;
    Endpoint endpoint;
    bool monitorReads;
    bool monitorWrites;
};

class SocketMonitor
{
   public:
    static SocketMonitor& get();
    ~SocketMonitor();

    void startMonitor(const MonitorInfo& monitorInfo);
    void stopMonitor(int fd);

   private:
    SocketMonitor();

    int pollFd{-1};
};