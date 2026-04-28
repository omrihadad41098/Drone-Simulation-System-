#ifndef __TurnRight_h__
#define __TurnRight_h__

#include "Cmd/Command.h"

namespace jb
{

class Compass;

class CmdTurnRight : public Command 
{
public:
	CmdTurnRight(Compass &compass) : m_compass(compass) { }

	virtual ExecuteResult execute(std::ostream& out) const override;

private:
	Compass &m_compass;
};

} 

#endif
