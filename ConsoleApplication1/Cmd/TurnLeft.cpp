#include "Cmd/TurnLeft.h"
#include "Compass.h"
#include <iostream>

namespace jb
{

ExecuteResult CmdTurnLeft::execute(std::ostream& out) const
{
	turnLeft(&m_compass);
	out << "turned left. now facing " << m_compass.getHeading() << std::endl;
	return { ExecuteStatus::Success };
}


} // jb
