#include "WorldOccupancy.h"

namespace jb
{
    bool WorldOccupancy::addDrone(size_t droneId, const Position& pos)
    {
        std::pair<std::map<Position,size_t>::iterator, bool> result = m_dronesByPosition.emplace(pos, droneId);
        return result.second;
    }

    bool WorldOccupancy::hasDroneAt(const Position& pos) const
    {
        return m_dronesByPosition.find(pos) != m_dronesByPosition.end();
    }

    bool WorldOccupancy::getDroneAt(const Position& pos, size_t& droneId) const
    {
        std::map<Position, size_t>::const_iterator it = m_dronesByPosition.find(pos);
        if (it == m_dronesByPosition.end())
        {
            return false;
        }

        droneId = it->second;
        return true;
    }

    bool WorldOccupancy::moveDrone(size_t droneId, const Position& from, const Position& to)
    {
        std::map<Position, size_t>::iterator fromIt = m_dronesByPosition.find(from);
        if (fromIt == m_dronesByPosition.end())
        {
            return false;
        }

        if (fromIt->second != droneId)
        {
            return false;
        }

        if (m_dronesByPosition.find(to) != m_dronesByPosition.end())
        {
            return false;
        }

        m_dronesByPosition.erase(fromIt);
        m_dronesByPosition.emplace(to, droneId);

        return true;
    }

    void WorldOccupancy::removeDrone(const Position& pos)
    {
        m_dronesByPosition.erase(pos);
    }
}