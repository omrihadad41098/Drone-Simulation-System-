#ifndef DRONENETWORKHANDLER_H
#define DRONENETWORKHANDLER_H

#include <iostream>
#include "NetworkHandler.h"

class DroneNetworkHandler : public whytsoft::NetworkHandler
{
public:
    explicit DroneNetworkHandler(unsigned short port)
        : whytsoft::NetworkHandler(port)
    {
    }

private:
    void onNewConnection(size_t socketId) const override
    {
        std::cout << "New connection: " << socketId << std::endl;
    }

    void onConnectionClosed(size_t socketId) const override
    {
        std::cout << "Connection closed: " << socketId << std::endl;
    }
};

#endif