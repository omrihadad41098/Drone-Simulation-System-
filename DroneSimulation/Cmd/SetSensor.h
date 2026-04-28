#ifndef __SETSENSOR_H__
#define __SETSENSOR_H__

#include <ostream>

#include "Command.h"
#include "SensorType.h"
#include "DroneCapabilities.h"

namespace jb
{
    class CmdSetSensor : public Command
    {
    public:
        CmdSetSensor(SensorType& currentSensor,
            const DroneCapabilities& capabilities,
            SensorType newSensor);

            virtual ExecuteResult execute(std::ostream& out) const override;

    private:
        SensorType& m_currentSensor;
        const DroneCapabilities& m_capabilities;
        SensorType m_newSensor;
    };
}

#endif