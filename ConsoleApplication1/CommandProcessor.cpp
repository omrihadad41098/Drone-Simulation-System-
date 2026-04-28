#include "CommandProcessor.h"
#include "DroneExecutor.h"

#include <string>
#include <sstream>
#include <WinSock2.h>



namespace jb
{
    CommandProcessor::CommandProcessor(std::map<size_t, ClientSession>& sessions,
        WorldOccupancy& occupancy, DroneNetworkHandler& nh)
        : m_sessions(sessions),
        m_occupancy(occupancy),
        m_nh(nh)
    { }

    bool CommandProcessor::handleClientCommand(size_t socketId,
        const std::string_view& commandName,
        std::ostream& out)
    {
        ClientSession& session = m_sessions.at(socketId);
        ExecuteResult result = session.executor->execute(commandName, out);
        if (!result.deadDroneIds.empty())
        {
            handleDeadDrones(result.deadDroneIds);
        }

        if (result.status == ExecuteStatus::Collision)
        {
            handleCollision(socketId, *result.otherDroneId);
            return false;
        }

        return true;
    }

    void CommandProcessor::handleCollision(size_t firstSocketId, size_t secondSocketId)
    {
        auto firstIt = m_sessions.find(firstSocketId);
        auto secondIt = m_sessions.find(secondSocketId);

        Position firstPosition = firstIt->second.drone->getPosition();
        Position secondPosition = secondIt->second.drone->getPosition();

        m_occupancy.removeDrone(firstPosition);
        m_occupancy.removeDrone(secondPosition);

        m_nh.PutOutput(firstSocketId, "drone is boomed with another, to restart press anything\n");
        m_nh.PutOutput(secondSocketId, "drone is boomed with another, to restart press anything\n");

        closesocket(firstSocketId);
        closesocket(secondSocketId);

        m_sessions.erase(firstSocketId);
        m_sessions.erase(secondSocketId);
    }

    void CommandProcessor::sendResponse(size_t socketId, std::ostream& out)
    {
        ClientSession& session = m_sessions.at(socketId);
        Drone& drone = *session.drone;

        std::string response = static_cast<std::ostringstream&>(out).str();
        response += "battery: " + std::to_string(drone.getCurrentBattery()) + "\n";

        m_nh.PutOutput(socketId, response);
    }

    void CommandProcessor::handleDeadDrones(const std::vector<size_t>& deadDroneIds)
    {
        for (size_t droneId : deadDroneIds)
        {
            std::map<size_t,ClientSession>::iterator it = m_sessions.find(droneId);
            if (it == m_sessions.end())
            {
                continue;
            }

            ClientSession& session = it->second;

            if (session.drone.has_value())
            {
                const Position& pos = session.drone->getPosition();
                m_occupancy.removeDrone(pos);
            }

            m_nh.PutOutput(droneId, "You died by a mine, press anything to restart\n");
            closesocket(droneId);
            m_sessions.erase(it);
        }

    }
}