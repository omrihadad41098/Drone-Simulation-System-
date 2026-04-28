#include "WorldGrid.h"
namespace jb
{

    WorldGrid::const_iterator::const_iterator(const WorldGrid &world, const Position& from, const Position& afterTo)
        : m_world(world), m_current(from), m_from(from), m_afterTo(afterTo)
    {}
    
    const Tile& WorldGrid::const_iterator::operator*() const
    {
        return m_world.getTile(m_current.getX(), m_current.getY());
    }

    WorldGrid::const_iterator& WorldGrid::const_iterator::operator++()
    {
        int nextX = m_current.getX() + 1;
        int nextY = m_current.getY();
        if (nextX >= m_afterTo.getX())
        {
            nextX = m_from.getX();
            nextY++;
        }
        m_current = Position(nextX, nextY);
        return *this;     
    }

    bool WorldGrid::const_iterator::operator!=(const const_iterator& other) const
    {
        return &m_world != &other.m_world ||
            m_current.getX() != other.m_current.getX() ||
            m_current.getY() != other.m_current.getY();
    }

    bool WorldGrid::const_iterator::operator==(const const_iterator& other) const
    {
        return !(*this != other);
    }

    
}