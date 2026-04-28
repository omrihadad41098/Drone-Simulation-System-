#include "DroneExecutor.h"
#include "Tile.h"

namespace jb
{
    DroneExecutor::DroneExecutor(Drone& drone, WorldOccupancy& occupancy, size_t droneId, MineManager& mineManager, size_t& minesLeft)
        : m_drone(drone),
        m_occupancy(occupancy),
        m_droneId(droneId),
        m_mineManager(mineManager),
        m_minesLeft(minesLeft),
        m_forward(drone.getWorld(), drone.getPosition(), drone.getCompass(), m_occupancy, m_droneId),
        m_left(m_drone.getCompass()),
        m_right(m_drone.getCompass()),
        m_mapCmd(m_drone.getWorld(), occupancy, droneId ),
        m_pov(m_drone.getWorld(),
            m_drone.getPosition(),
            m_drone.getCompass(),
            m_drone.getSensorType(),
            occupancy,droneId),
        m_setA(m_drone.getSensorType(), m_drone.getCapabilities(), SENSOR_A),
        m_setB(m_drone.getSensorType(), m_drone.getCapabilities(), SENSOR_B),
        m_setC(m_drone.getSensorType(), m_drone.getCapabilities(), SENSOR_C),
        m_putMine(mineManager ,drone.getPosition(), droneId, minesLeft)
    {
        m_commands =
        {
            { "fwd", &m_forward },
            { "+90", &m_right },
            { "-90", &m_left },
            { "pov", &m_pov },
            { "s-a", &m_setA },
            { "s-b", &m_setB },
            { "s-c", &m_setC },
            { "map", &m_mapCmd },
            {"mine", &m_putMine}
        };
    }

    ExecuteResult DroneExecutor::execute(const std::string_view& commandName, std::ostream& out)
    {
        std::map<std::string_view, Command*>::const_iterator it = m_commands.find(commandName);

        if (it == m_commands.end())
        {
            out << "Unknown Command";
            return { ExecuteStatus::Blocked };
        }

        Command* cmd = it->second;
        unsigned int requiredEnergy = cmd->getEnergyConsumption();

        if (m_drone.getCurrentBattery() < requiredEnergy)
        {
            out << "not enough energy for this action";
            return { ExecuteStatus::Blocked };
        }

        ExecuteResult result = cmd->execute(out);

        if (result.status == ExecuteStatus::Success)
        {
            m_drone.consumeBattery(requiredEnergy);

            if (m_drone.getWorld().getTile(
                m_drone.getPosition().getX(),
                m_drone.getPosition().getY()).isCharging())
            {
                m_drone.rechargeToMax();
                out << "charged to full" << std::endl;
            }

            if (commandName == "fwd" && m_mineManager.hasMineAt(m_drone.getPosition()))
            {
                out << "BOOM! drone stepped on a mine" << std::endl;
                result.deadDroneIds =m_mineManager.explodeMineAt(m_drone.getPosition());;
            }
        }

        return result;
    }
}