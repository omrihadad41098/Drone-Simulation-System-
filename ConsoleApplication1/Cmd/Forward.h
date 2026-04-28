#ifndef __CmdForward_h__
#define __CmdForward_h__

#include <iostream>
#include "Cmd/Command.h"

#include "WorldGrid.h"
#include "Position.h"
#include "Compass.h"
#include "WorldOccupancy.h"

namespace jb
{

    class CmdForward : public Command
    {
    public:
        CmdForward(const WorldGrid& grid,
            Position& position,
            const Compass& compass,
            WorldOccupancy& occupancy,
            size_t droneId)
            : m_grid(grid),
            m_position(position),
            m_compass(compass),
            m_occupancy(occupancy),
            m_droneId(droneId)
        {
        }

        virtual ExecuteResult execute(std::ostream& out) const override;

    private:
        const WorldGrid& m_grid;
        Position& m_position;
        const Compass& m_compass;
        WorldOccupancy& m_occupancy;
        size_t m_droneId;
    };

}

#endif