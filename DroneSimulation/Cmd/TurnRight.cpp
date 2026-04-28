#include "Cmd/TurnRight.h"
#include "Compass.h"
#include <iostream>

namespace jb
{

	ExecuteResult CmdTurnRight::execute(std::ostream& out) const
{
	turnRight(&m_compass);
	out << "turned right. now facing " << m_compass.getHeading() << std::endl;
	return { ExecuteStatus::Success };
}


} // jb
