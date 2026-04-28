#include "WorldGrid.h"

#include <algorithm>
#include <stdexcept>
#include <string>
#include <iostream>

#include "Compass.h"
#include "EmptyTile.h"
#include "ExitTile.h"
#include "Position.h"
#include "WallTile.h"
#include "ChargeTile.h"


namespace jb
{
	static EmptyTile EMPTY{};
	static WallTile WALL{};
	static ExitTile EXIT{};
	static ChargeTile CHARGE{};

	static std::map<char, Tile*> tilesByCharMap =
	{
		{ '#', &WALL },
		{ 'E', &EXIT },
		{ 'C', &CHARGE },
		{ ' ', &EMPTY }
	};

	size_t WorldGrid::getRowSize() const
	{
		return m_rowSize;
	}

	size_t WorldGrid::getNumRows() const
	{
		return m_numRows;
	}

	WorldGrid::WorldGrid()
		: m_grid{}, m_rowSize(0), m_numRows(0)
	{
		loadDefaultMap();
	}

	WorldGrid::WorldGrid(std::istream& input)
		: m_grid{}, m_rowSize(0), m_numRows(0)
	{
		loadFromStream(input);
	}

	void WorldGrid::initializeAsEmpty(std::size_t width, std::size_t height)
	{
		m_rowSize = width;
		m_numRows = height;
		m_grid.assign(m_numRows, Row(m_rowSize, &EMPTY));
	}

	void WorldGrid::loadDefaultMap()
	{
		initializeAsEmpty(5, 6);

		m_grid[0][0] = &WALL;
		m_grid[1][1] = &WALL;
		m_grid[2][2] = &WALL;
		m_grid[3][3] = &WALL;
		m_grid[4][0] = &WALL;
		m_grid[4][3] = &WALL;
		m_grid[5][1] = &WALL;
		m_grid[5][4] = &EXIT;
	}

	void WorldGrid::loadFromStream(std::istream& input)
	{
		std::vector<std::string> lines;
		std::string line;
		std::size_t maxWidth = 0;

		while (std::getline(input, line))
		{
			lines.push_back(line);
			maxWidth = std::max(maxWidth, line.size());
		}

		if (lines.empty())
		{
			loadDefaultMap();
			return;
		}

		initializeAsEmpty(maxWidth, lines.size());

		for (std::size_t y = 0; y < lines.size(); ++y)
		{
			for (std::size_t x = 0; x < lines[y].size(); ++x)
			{
				std::map<char, Tile*>::const_iterator it = tilesByCharMap.find(lines[y][x]);
				if (it == tilesByCharMap.end())
				{
					continue;
				}

				m_grid[y][x] = it->second;
			}
		}
	}

	Tile& WorldGrid::getTile(int x, int y) const
	{
		if (x < 0 || y < 0)
		{
			return WALL;
		}
		if (static_cast<std::size_t>(x) >= m_rowSize || static_cast<std::size_t>(y) >= m_numRows)
		{
			return WALL;
		}

		Tile* tile = m_grid[y][x];
		return tile ? *tile : EMPTY;
	}



	char WorldGrid::tileToChar(const Tile& tile)
	{
		if (tile.shouldExit())
		{
			return 'E';
		}
		if (tile.isCharging())
		{
			return 'C';
		}
		return tile.canOccupy() ? ' ' : '#';
	}

	WorldGrid::const_iterator WorldGrid::begin(const Position& from, const Position& afterTo) const
	{
		return const_iterator(*this, from, afterTo);
	}

	WorldGrid::const_iterator WorldGrid::end(const Position& from, const Position& afterTo) const
	{
		const_iterator it = const_iterator(*this, from, afterTo);
		it.m_current = Position(from.getX(), afterTo.getY());
		return it;
	}


	WorldGrid::CharGrid WorldGrid::getRectangle(const Position& from, const Position& afterTo) const
	{
		CharGrid rectangle{};
		const int width = afterTo.getX() - from.getX();

		CharRow currentRow{};
		currentRow.reserve(width);

		for (const_iterator it = begin(from, afterTo); it != end(from, afterTo); ++it)
		{
			currentRow.push_back(tileToChar(*it));

			if (static_cast<int>(currentRow.size()) == width)
			{
				rectangle.push_back(currentRow);
				currentRow.clear();
			}
		}

		return rectangle;

	}

	char WorldGrid::getCharAt(int x, int y) const
	{
		return tileToChar(getTile(x, y));
	}

	void WorldGrid::printMap(std::ostream& out, const WorldOccupancy& occupancy, size_t selfId) const
	{
		for (std::size_t y = 0; y < m_numRows; ++y)
		{
			for (std::size_t x = 0; x < m_rowSize; ++x)
			{
				Position pos(static_cast<int>(x), static_cast<int>(y));

				size_t droneId = 0;
				if (occupancy.getDroneAt(pos, droneId))
				{
					if (droneId == selfId)
					{
						out << 'X';
					}
					else
					{
						out << 'D';
					}
				}
				else
				{
					out << tileToChar(*m_grid[y][x]);
				}
				
			}
			out << "\n";

		}
	}
}