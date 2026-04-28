#include "Cmd/Forward.h"
#include "Tile.h"

namespace jb
{

    ExecuteResult CmdForward::execute(std::ostream& out) const
    {
        Position oldPosition = m_position;
        Position newPosition = advance(m_position, m_compass);

        if (!m_grid.getTile(newPosition.getX(), newPosition.getY()).canOccupy())
        {
            out << "blocked" << std::endl;
            return { ExecuteStatus::Blocked };
        }

        if (m_occupancy.hasDroneAt(newPosition))
        {
            out << "collision" << std::endl;
            std::size_t otherDroneId = 0;
            m_occupancy.getDroneAt(newPosition, otherDroneId);
            return { ExecuteStatus::Collision, otherDroneId };
        }

        out << "forward" << std::endl;

        m_position = newPosition;
        m_occupancy.moveDrone(m_droneId, oldPosition, newPosition);

        return { ExecuteStatus::Success };
    }

} 