#ifndef __ExitTile_h__
#define __ExitTile_h__

#include "Tile.h"

namespace jb
{

struct ExitTile : public Tile 
{
	ExitTile() : Tile(EXIT) { }
	virtual bool canOccupy() const { return true; }
};

} 
#endif
