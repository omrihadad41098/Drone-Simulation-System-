#include "Cmd/SetSensor.h"

namespace jb
{
    CmdSetSensor::CmdSetSensor(SensorType& currentSensor,
        const DroneCapabilities& capabilities,
        SensorType newSensor)
        : m_currentSensor(currentSensor),
        m_capabilities(capabilities),
        m_newSensor(newSensor)
    {
    }

    ExecuteResult CmdSetSensor::execute(std::ostream& out) const
    {
        if (!m_capabilities.supportsSensor(m_newSensor))
        {
            out << "sensor not supported";
            return {ExecuteStatus::Blocked};
        }

        if (m_currentSensor == m_newSensor)
        {
            out << "sensor already selected";
            return { ExecuteStatus::Blocked };
        }

        m_currentSensor = m_newSensor;
        out << "sensor changed";
        return { ExecuteStatus::Success };
    }
}