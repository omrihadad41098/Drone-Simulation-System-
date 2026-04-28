#ifndef __CmdPov_h__
#define __CmdPov_h__

#include "Cmd/Command.h"
#include "WorldGrid.h"
#include "SensorType.h"
#include "WorldOccupancy.h"

#include <vector>

namespace jb
{

class Position;
class Compass;

class CmdPov : public Command
{
public:
	CmdPov(const WorldGrid& grid, const Position& position, const Compass& heading, 
		SensorType& sensorType, WorldOccupancy& occupancy, size_t droneId)
		: m_grid(grid), m_position(position), m_heading(heading), m_sensorType(sensorType),
		m_occupancy(occupancy), m_droneId(droneId)  {}

	virtual ExecuteResult execute(std::ostream& out) const override;
	virtual unsigned int getEnergyConsumption() const override;
	WorldGrid::CharGrid getPov() const;

private:
	const WorldGrid &m_grid;
	const Position &m_position;
	const Compass &m_heading;
	SensorType& m_sensorType;
	WorldOccupancy& m_occupancy;
	size_t m_droneId;

	
	
	struct RectangleBounds
	{
		Position from;
		Position afterTo;
		RectangleBounds(const Position& from, const Position& afterTo)
			: from(from), afterTo(afterTo) {
		}
	};

	Position translateRelative(int rightOffset, int forwardOffset) const;
	RectangleBounds getRectangleBounds(int rightMin,
		int rightMax,
		int forwardMin,
		int forwardMax) const;

	char getCharFromRectangle(const WorldGrid::CharGrid& rect,
		const RectangleBounds& bounds,
		int rightOffset,
		int forwardOffset) const;
};

} 

#endif
