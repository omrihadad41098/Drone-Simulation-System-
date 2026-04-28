#ifndef MINE_H
#define MINE_H

#include "Position.h"

#include <cstddef>
#include <chrono>

namespace jb
{
    class Mine
    {
    public:
        Mine(size_t ownerDroneId, const Position& position);

        size_t getOwnerDroneId() const;
        const Position& getPosition() const;
        bool isExpired() const;

    private:
        size_t m_ownerDroneId;
        Position m_position;
        std::chrono::steady_clock::time_point m_expireTime;
    };
}

#endif