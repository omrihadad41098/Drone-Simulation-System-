#ifndef __CmdMap_h__
#define __CmdMap_h__

#include "Cmd/Command.h"
#include "WorldGrid.h"

namespace jb
{

    class CmdMap : public Command
    {
    public:
        CmdMap(const WorldGrid& grid, const WorldOccupancy& occupancy, size_t droneId) :
            m_grid(grid), m_occupancy(occupancy), m_droneId(droneId)
        {}

        virtual ExecuteResult execute(std::ostream& out) const override
        {
            m_grid.printMap(out, m_occupancy, m_droneId);
            return { ExecuteStatus::Success };
        }

    private:
        const WorldGrid& m_grid;
        const WorldOccupancy& m_occupancy;
        size_t m_droneId;
    };

}

#endif