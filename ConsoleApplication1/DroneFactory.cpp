#include "DroneFactory.h"

#include <map>

namespace jb
{
    Drone DroneFactory::create(WorldGrid& world, DroneType type)
    {
        static const std::map<DroneType, DroneCapabilities> configs =
        {
            { DRONE_A, DroneCapabilities({ SENSOR_C }, 300) },
            { DRONE_B, DroneCapabilities({ SENSOR_A, SENSOR_B }, 500) },
            { DRONE_C, DroneCapabilities({ SENSOR_C }, 400) }
        };

        std::map<DroneType, DroneCapabilities>::const_iterator it = configs.find(type);

        if (it != configs.end())
        {
            return Drone(world, it->second);
        }

        return Drone(world, DroneCapabilities({ SENSOR_A, SENSOR_B, SENSOR_C }, 1000));
    }
}