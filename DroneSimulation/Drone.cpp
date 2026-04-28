#include "Drone.h"

namespace jb
{
    Drone::Drone(WorldGrid& world, const DroneCapabilities& droneCapabilities)
        : m_world(world),
        m_position(0, 0),
        m_compass(),
        m_sensorType(droneCapabilities.getInitialSensor()),
        m_droneCapabilities(droneCapabilities),
        m_currentBattery(droneCapabilities.getMaxBattery())
    {  }

    void Drone::rechargeToMax()
    {
        m_currentBattery= m_droneCapabilities.getMaxBattery();
    }

    size_t Drone::getCurrentBattery() const
    {
        return m_currentBattery;
    }

    void Drone::consumeBattery(unsigned int amount)
    {
        m_currentBattery -= amount;
    }

    WorldGrid& Drone::getWorld()
    {
        return m_world;
    }

    Position& Drone::getPosition()
    {
        return m_position;
    }

    Compass& Drone::getCompass()
    {
        return m_compass;
    }

    SensorType& Drone::getSensorType()
    {
        return m_sensorType;
    }

    const DroneCapabilities& Drone::getCapabilities() const
    {
        return m_droneCapabilities;
    }
}