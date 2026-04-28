#include "Position.h"
#include <map>
#include <stdexcept>

namespace jb
{

struct PositionDelta
{
	int deltaX;
	int deltaY;
};

using DeltasMap = std::map<Compass, const PositionDelta>;
static const DeltasMap DELTAS{
	{ NORTH, { 0, -1 } },
	{ EAST,  { 1,  0 } },
	{ SOUTH, { 0,  1 } },
	{ WEST,  { -1, 0 } }
};

Position advance(const Position &cur, const Compass &heading)
{
	DeltasMap::const_iterator deltaItr = DELTAS.find(heading);
	if (deltaItr == DELTAS.end())
	{
		throw std::runtime_error{"Unprocessable compass heading"};
	}
	return Position(cur.getX() + deltaItr->second.deltaX, cur.getY() + deltaItr->second.deltaY);
}

bool Position::operator<(const Position& other) const
{
	if (m_x != other.m_x)
	{
		return m_x < other.m_x;
	}

	return m_y < other.m_y;
}

bool Position::operator==(const Position& other) const
{
	return other.getX() == this->m_x && other.getX() == this->getY();
}
} // jb
