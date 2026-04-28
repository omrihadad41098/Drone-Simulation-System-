#ifndef __TurnLeft_h__
#define __TurnLeft_h__

#include "Cmd/Command.h"

namespace jb
{

class Compass;

class CmdTurnLeft : public Command 
{
public:
	CmdTurnLeft(Compass &compass) : m_compass(compass) { }

	virtual ExecuteResult execute(std::ostream& out) const override;

private:
	Compass &m_compass;
};

} 

#endif
