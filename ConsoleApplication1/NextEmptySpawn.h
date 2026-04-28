#ifndef __NextEmptySpawn_h__
#define __NextEmptySpawn_h__

#include "WorldGrid.h"
#include "WorldOccupancy.h"
#include "Position.h"

namespace jb
{
    class NextEmptySpawn
    {
    public:
        NextEmptySpawn(const WorldGrid& world, const WorldOccupancy& occupancy);

        Position getNextEmptySpawn() const;

    private:
        const WorldGrid& m_world;
        const WorldOccupancy& m_occupancy;
    };
}

#endif