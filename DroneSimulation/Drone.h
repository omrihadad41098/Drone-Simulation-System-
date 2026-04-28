#ifndef __Drone_h__
#define __Drone_h__

#include "WorldGrid.h"
#include "Compass.h"
#include "Position.h"
#include "SensorType.h"
#include "DroneCapabilities.h"

namespace jb
{
    class Drone
    {
    public:
        Drone(WorldGrid& world, const DroneCapabilities& droneCapabilities);

        size_t getCurrentBattery() const;
        void consumeBattery(unsigned int amount);

        WorldGrid& getWorld();
        Position& getPosition();
        Compass& getCompass();
        SensorType& getSensorType();
        const DroneCapabilities& getCapabilities() const;
        void rechargeToMax();


    private:
        WorldGrid& m_world;
        Position m_position;
        Compass m_compass;
        SensorType m_sensorType;
        DroneCapabilities m_droneCapabilities;
        size_t m_currentBattery;

    };
}

#endif