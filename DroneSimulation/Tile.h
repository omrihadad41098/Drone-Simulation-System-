#ifndef __Tile_h__
#define __Tile_h__

#include "BaseEssentials.h"

namespace jb
{

class Tile : private BaseEssentials 
{
public:
	enum ExitBehavior { KEEP_GOING, EXIT };
	Tile(ExitBehavior exitBehavior = KEEP_GOING) : m_exitBehavior(exitBehavior) { }

	bool shouldExit() const { return m_exitBehavior == EXIT; }
	virtual bool isCharging() const { return false; }

	virtual bool canOccupy() const = 0;

private:
	const ExitBehavior m_exitBehavior;
};

} 

#endif
