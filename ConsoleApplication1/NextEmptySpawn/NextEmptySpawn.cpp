#include "NextEmptySpawn.h"

#include "Tile.h"

namespace jb
{
    NextEmptySpawn::NextEmptySpawn(const WorldGrid& world, const WorldOccupancy& occupancy)
        : m_world(world), m_occupancy(occupancy)
    {
    }

    Position NextEmptySpawn::getNextEmptySpawn() const
    {
        for (int y = 0; y < static_cast<int>(m_world.getNumRows()); ++y)
        {
            for (int x = 0; x < static_cast<int>(m_world.getRowSize()); ++x)
            {
                Position pos((x),(y));
                Tile& tile = m_world.getTile((x), (y));

                if (!tile.canOccupy())
                {
                    continue;
                }

                if (tile.shouldExit())
                {
                    continue;
                }

                if (m_occupancy.hasDroneAt(pos))
                {
                    continue;
                }

                return pos;
            }
        }

        return Position(-1, -1);
    }
}