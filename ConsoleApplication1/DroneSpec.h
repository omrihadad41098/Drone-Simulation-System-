#ifndef __DroneSpec_h__
#define __DroneSpec_h__

#include "Cmd/Pov.h"

namespace jb
{

    struct DroneSpec
    {
        bool supportsA = false;
        bool supportsB = false;
        bool supportsC = false;
        unsigned int battery = 0;

        bool supportsSensor(SensorType sensor) const
        {
            switch (sensor)
            {
            case SENSOR_A: return supportsA;
            case SENSOR_B: return supportsB;
            case SENSOR_C: return supportsC;
            default:       
                return false;
            }
        }

        SensorType getInitialSensor() const
        {
            if (supportsA) return SENSOR_A;
            if (supportsB) return SENSOR_B;
            return SENSOR_C;
        }
    };

}

#endif