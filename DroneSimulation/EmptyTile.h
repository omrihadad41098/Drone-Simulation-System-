#ifndef __EmptyTile_h__
#define __EmptyTile_h__

#include "Tile.h"

namespace jb
{

class EmptyTile : public Tile 
{
	virtual bool canOccupy() const { return true; }
};

}

#endif
