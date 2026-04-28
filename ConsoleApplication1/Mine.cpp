#include "Mine.h"

namespace jb
{
    Mine::Mine(size_t ownerDroneId, const Position& position)
        : m_ownerDroneId(ownerDroneId),
        m_position(position),
        m_expireTime(std::chrono::steady_clock::now() + std::chrono::seconds(10))
    {
    }

    size_t Mine::getOwnerDroneId() const
    {
        return m_ownerDroneId;
    }

    const Position& Mine::getPosition() const
    {
        return m_position;
    }

    bool Mine::isExpired() const
    {
        return std::chrono::steady_clock::now() >= m_expireTime;
    }
}