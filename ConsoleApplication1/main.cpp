#include <fstream>
#include <map>
#include <string>
#include <string_view>
#include <sstream>
#include <optional>
#include <memory>

#include "WorldGrid.h"
#include "Drone.h"
#include "DroneNetworkHandler.h"
#include "Tile.h"
#include "Cmd/Command.h"
#include "DroneFactory.h"
#include "DroneExecutor.h"
#include "NextEmptySpawn.h"
#include "ClientSession.h"
#include "CommandProcessor.h"

#pragma comment(lib, "Ws2_32.lib")

using namespace jb;

static void chooseDrone(int& choice, std::string input);
static void isReachedExit(Drone& drone, size_t socketId, DroneNetworkHandler& nh, std::map<size_t, ClientSession>& sessions);
int main()
{
    std::ifstream mapFile("map.txt");
    WorldGrid world = mapFile ? WorldGrid(mapFile) : WorldGrid();
    WorldOccupancy occupancy{};
    NextEmptySpawn spawnFinder(world, occupancy);
    DroneNetworkHandler nh{ 9000 };

    std::map<size_t, ClientSession> sessions;
    CommandProcessor processor(sessions, occupancy, nh);
    MineManager mineManager(
        occupancy,
        [&](const std::vector<size_t>& deadDrones)
        {
            processor.handleDeadDrones(deadDrones);
        });
    while (true)
    {
        size_t socketId = 0;
        std::string input;
        nh.GetInput(&socketId, &input);

        std::pair<std::map<size_t, ClientSession>::iterator, bool> result =sessions.try_emplace(socketId);
        std::map<size_t, ClientSession>::iterator it = result.first;
        ClientSession& session = it->second;

        if (!session.droneChosen)
        {
            nh.PutOutput(socketId,
                "choose drone:\n"
                "1 - drone A (sensor C, battery 300)\n"
                "2 - drone B (sensors A,B, battery 500)\n"
                "3 - drone C (sensor C, battery 400)\n"
                "anything else - default (sensors A,B,C, battery 1000)\n");

            nh.GetInput(&socketId, &input);

            int choice = 0;
            chooseDrone(choice, input);
            DroneType droneType = static_cast<DroneType>(choice);

            Position spawn = spawnFinder.getNextEmptySpawn();
            if (spawn.getX() == -1 && spawn.getY() == -1)
            {
                nh.PutOutput(socketId, "no free spawn position left\n");
                continue;
            }

            session.drone.emplace(DroneFactory::create(world, droneType));
            session.drone->getPosition() = spawn;
            
            session.minesLeft = session.generateRandomMines();

            nh.PutOutput(socketId, "Drone selected. Mines: " + std::to_string(session.minesLeft) + "\n");

            occupancy.addDrone(socketId, spawn);

            session.executor = std::unique_ptr<DroneExecutor>(new DroneExecutor(*session.drone, occupancy, socketId, mineManager, session.minesLeft));
            session.droneChosen = true;

   
            continue;
        }

        std::ostringstream out;

        bool isStillAlive = processor.handleClientCommand(socketId, input, out);
        if (!isStillAlive)
        {
            continue;
        }

        ClientSession& currentSession = sessions.at(socketId);
        Drone& drone = *currentSession.drone;

        processor.sendResponse(socketId, out);
        isReachedExit(drone, socketId, nh, sessions);
        
    }

    return 0;
}
    static void chooseDrone(int& choice, std::string input)
    {
        try
        {
            choice = std::stoi(input);
            if (choice < 1 || choice > 3)
            {
                choice = 0;
            }
        }
        catch (const std::exception&)
        {
            choice = 0;
        }

    }

    static void isReachedExit(Drone &drone , size_t socketId, DroneNetworkHandler& nh, std::map<size_t, ClientSession>& sessions) {
        if (drone.getWorld().getTile(
            drone.getPosition().getX(),
            drone.getPosition().getY()).shouldExit())
        {
            nh.PutOutput(socketId, "you reached the exit, press anything to restart\n");
            closesocket(socketId);
            sessions.erase(socketId);
        }
    }