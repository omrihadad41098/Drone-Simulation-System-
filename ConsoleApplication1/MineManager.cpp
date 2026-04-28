#include "MineManager.h"

#include <chrono>

namespace jb
{
    MineManager::MineManager(WorldOccupancy& occupancy, ExplosionCallback onExplosion)
        : m_occupancy(occupancy),
        m_onExplosion(onExplosion),
        m_running(true),
        m_worker(&MineManager::workerLoop, this)
    {
    }

    MineManager::~MineManager()
    {
        m_running = false;

        if (m_worker.joinable())
        {
            m_worker.join();
        }
    }

    void MineManager::addMine(size_t ownerDroneId, const Position& position)
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_mines.emplace_back(ownerDroneId, position);
    }

    bool MineManager::hasMineAt(const Position& position) const
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        for (size_t i = 0; i < m_mines.size(); ++i)
        {
            if (m_mines[i].getPosition() == position)
            {
                return true;
            }
        }

        return false;
    }

    void MineManager::removeMineAt(const Position& position)
    {
        std::lock_guard<std::mutex> lock(m_mutex);

        for (size_t i = 0; i < m_mines.size(); )
        {
            if (m_mines[i].getPosition() == position)
            {
                m_mines.erase(m_mines.begin() + i);
            }
            else
            {
                ++i;
            }
        }
    }

    std::vector<size_t> MineManager::explodeMineAt(const Position& position)
    {
        removeMineAt(position);
        return collectDeadDronesInRadius(position);
    }

    std::vector<size_t> MineManager::collectDeadDronesInRadius(const Position& position) const
    {
        std::vector<size_t> deadDrones;

        int centerX = position.getX();
        int centerY = position.getY();

        for (int dx = -1; dx <= 1; ++dx)
        {
            for (int dy = -1; dy <= 1; ++dy)
            {
                Position current(centerX + dx, centerY + dy);

                size_t droneId = 0;
                if (m_occupancy.getDroneAt(current, droneId))
                {
                    deadDrones.push_back(droneId);
                }
            }
        }

        return deadDrones;
    }

    void MineManager::workerLoop()
    {
        while (m_running)
        {
            explodeExpiredMines();
            std::this_thread::sleep_for(std::chrono::milliseconds(100));
        }
    }

    void MineManager::explodeExpiredMines()
    {
        std::vector<Position> expiredPositions;

        {
            std::lock_guard<std::mutex> lock(m_mutex);

            for (size_t i = 0; i < m_mines.size(); )
            {
                if (m_mines[i].isExpired())
                {
                    expiredPositions.push_back(m_mines[i].getPosition());
                    m_mines.erase(m_mines.begin() + i);
                }
                else
                {
                    ++i;
                }
            }
        }

        for (size_t i = 0; i < expiredPositions.size(); ++i)
        {
            std::vector<size_t> deadDrones =
                collectDeadDronesInRadius(expiredPositions[i]);

            if (!deadDrones.empty() && m_onExplosion)
            {
                m_onExplosion(deadDrones);
            }
        }
    }
}