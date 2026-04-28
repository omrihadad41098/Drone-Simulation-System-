#ifndef __DroneCapabilities_h__
#define __DroneCapabilities_h__

#include <vector>
#include <algorithm>

#include "SensorType.h"

namespace jb
{

    class DroneCapabilities
    {
    public:

        DroneCapabilities(std::vector<SensorType> sensors, size_t maxBattery)
            : m_supportedSensors(std::move(sensors)), m_maxBattery(maxBattery)
        {
        }

        bool supportsSensor(SensorType sensor) const
        {
            return std::find(m_supportedSensors.begin(),m_supportedSensors.end(),
                sensor) != m_supportedSensors.end();
        }

        SensorType getInitialSensor() const
        {
            if (!m_supportedSensors.empty())
            {
                return m_supportedSensors.front();
            }

            return SENSOR_A;
        }

        const std::vector<SensorType>& getSupportedSensors() const
        {
            return m_supportedSensors;
        }

        size_t getMaxBattery() const {
            return m_maxBattery;
        }

    private:
        std::vector<SensorType> m_supportedSensors;
        size_t m_maxBattery;
    };

}
#endif