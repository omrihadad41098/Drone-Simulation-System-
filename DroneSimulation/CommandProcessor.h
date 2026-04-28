#ifndef COMMANDPROCESSOR_H
#define COMMANDPROCESSOR_H

#include <map>
#include <string_view>
#include <ostream>

#include "ClientSession.h"
#include "WorldOccupancy.h"
#include "ExecuteResult.h"
#include "DroneNetworkHandler.h"

namespace jb
{
    class CommandProcessor
    {
    public:
        CommandProcessor(std::map<size_t, ClientSession>& sessions,
            WorldOccupancy& occupancy, DroneNetworkHandler& nh);

        bool handleClientCommand(size_t socketId, const std::string_view& commandName, std::ostream& out);
        void sendResponse(size_t socketId, std::ostream& out);
        void handleDeadDrones(const std::vector<size_t>& deadDroneIds);
    private:
        void handleCollision(size_t firstSocketId, size_t secondSocketId);
        

    private:
        std::map<size_t, ClientSession>& m_sessions;
        WorldOccupancy& m_occupancy;
        DroneNetworkHandler& m_nh;
    };
}

#endif