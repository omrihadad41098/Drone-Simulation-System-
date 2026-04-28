#include "Cmd/Execute.h"
#include "Compass.h"
#include <iostream>

namespace jb
{

ExecuteResult CmdExecute::execute(std::ostream& out) const
{
	m_toExecute(out);
	return { ExecuteStatus::Success };
}


} // jb
