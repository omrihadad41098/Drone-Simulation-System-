#ifndef __DRONEEXECUTOR_H__
#define __DRONEEXECUTOR_H__

#include <map>
#include <string_view>
#include <ostream>

#include "Drone.h"
#include "Cmd/Command.h"
#include "Cmd/Forward.h"
#include "Cmd/TurnLeft.h"
#include "Cmd/TurnRight.h"
#include "Cmd/Pov.h"
#include "Cmd/Map.h"
#include "Cmd/SetSensor.h"
#include "FixedConsumption.h"
#include "SensorType.h"
#include "WorldOccupancy.h"
#include "ExecuteResult.h"
#include "Cmd/PutMine.h"

namespace jb
{
    using CommandsMap = std::map<std::string_view, Command*>;
    
    class DroneExecutor
    {
    public:
        explicit DroneExecutor(Drone& drone, WorldOccupancy& occupancy, size_t droneId, MineManager& mineManager, size_t& minesLeft);

        ExecuteResult execute(const std::string_view& commandName, std::ostream& out);

    private:
        Drone& m_drone;
        WorldOccupancy& m_occupancy;
        size_t m_droneId;
        MineManager& m_mineManager;
        size_t& m_minesLeft;

        FixedConsumption<CmdForward, 20> m_forward;
        FixedConsumption<CmdTurnLeft, 5> m_left;
        FixedConsumption<CmdTurnRight, 5> m_right;
        FixedConsumption<CmdMap, 80> m_mapCmd;
        CmdPov m_pov;
        FixedConsumption<CmdSetSensor, 30> m_setA;
        FixedConsumption<CmdSetSensor, 15> m_setB;
        FixedConsumption<CmdSetSensor, 50> m_setC;
        FixedConsumption<CmdPutMine, 40>m_putMine;
        

        CommandsMap m_commands;
    };
}

#endif