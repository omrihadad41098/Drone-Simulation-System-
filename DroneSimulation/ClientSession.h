#ifndef CLIENTSESSION_H
#define CLIENTSESSION_H

#include <random>
#include <optional>
#include <memory>
#include "Drone.h"
#include "DroneExecutor.h"


namespace jb
{

    struct ClientSession
    {
        size_t generateRandomMines()
        {
            static std::random_device rd;
            static std::mt19937 gen(rd());
            static std::uniform_int_distribution<size_t> dist(0, 3);

            return dist(gen);
        }

        bool droneChosen = false;
        std::optional<Drone> drone;
        std::unique_ptr<DroneExecutor> executor;
        size_t minesLeft = 0;
    };

        
        
        
}

#endif