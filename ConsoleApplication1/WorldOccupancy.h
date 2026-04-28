#ifndef __WorldOccupancy_h__
#define __WorldOccupancy_h__

#include <map>
#include <cstddef>

#include "Position.h"

namespace jb
{
    class WorldOccupancy
    {
    public:
        bool addDrone(size_t droneId, const Position& pos);
        bool hasDroneAt(const Position& pos) const;
        bool getDroneAt(const Position& pos, size_t& droneId) const;
        bool moveDrone(size_t droneId, const Position& from, const Position& to);
        void removeDrone(const Position& pos);

    private:
        std::map<Position, size_t> m_dronesByPosition;
    };
}

#endif