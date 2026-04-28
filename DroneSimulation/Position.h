#ifndef __Position_h__
#define __Position_h__

#include "Compass.h"

namespace jb
{

class Position
{
public:
	Position(int x, int y) : m_x(x), m_y(y) { }
	Position(const Position &other) = default;
	Position &operator=(const Position &other) = default;
	bool operator==(const Position& other) const;
	bool operator<(const Position& other) const;
	~Position() = default;

	int getX() const { return m_x; }
	int getY() const { return m_y; }

private:
	int m_x;
	int m_y;
};

Position advance(const Position &cur, const Compass &heading);

} 

#endif
