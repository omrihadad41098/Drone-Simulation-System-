#ifndef MINE_MANAGER_H
#define MINE_MANAGER_H

#include "Mine.h"
#include "Position.h"
#include "WorldOccupancy.h"

#include <vector>
#include <mutex>
#include <thread>
#include <atomic>
#include <functional>
#include <cstddef>

namespace jb
{
    class MineManager
    {
    public:
        using ExplosionCallback = std::function<void(const std::vector<size_t>&)>;

        MineManager(WorldOccupancy& occupancy, ExplosionCallback onExplosion);
        ~MineManager();

        MineManager(const MineManager&) = delete;
        MineManager& operator=(const MineManager&) = delete;

        void addMine(size_t ownerDroneId, const Position& position);
        bool hasMineAt(const Position& position) const;
        void removeMineAt(const Position& position);

        std::vector<size_t> explodeMineAt(const Position& position);

    private:
        void workerLoop();
        void explodeExpiredMines();
        std::vector<size_t> collectDeadDronesInRadius(const Position& position) const;

    private:
        mutable std::mutex m_mutex;
        std::vector<Mine> m_mines;

        WorldOccupancy& m_occupancy;
        ExplosionCallback m_onExplosion;

        std::thread m_worker;
        std::atomic<bool> m_running;
    };
}

#endif