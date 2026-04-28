#ifndef __Command_h__
#define __Command_h__
#include <ostream>

#include "BaseEssentials.h"
#include "ExecuteResult.h"

namespace jb
{

struct Command : private BaseEssentials
{
	virtual ExecuteResult execute(std::ostream& out) const = 0;
	virtual unsigned int getEnergyConsumption() const
	{
		return 0;
	}
};

}

#endif
