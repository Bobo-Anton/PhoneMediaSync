#pragma once

#include <cstdint>

#include "Types.hpp"

class Server
{
   public:
    Server() = default;
    ~Server();

    void init(uint16_t port);

   private:
    int serverFd{-1};
};