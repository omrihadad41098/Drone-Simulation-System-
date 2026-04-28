#ifndef __DroneFactory_h__
#define __DroneFactory_h__

#include "Drone.h"
#include "DroneCapabilities.h"
#include "SensorType.h"

namespace jb
{
    enum DroneType
    {
        DRONE_A = 1,
        DRONE_B = 2,
        DRONE_C = 3
    };

    class DroneFactory
    {
    public:
        static Drone create(WorldGrid& world, DroneType type);
    };
}

#endif