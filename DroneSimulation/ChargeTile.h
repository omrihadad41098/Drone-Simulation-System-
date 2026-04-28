#ifndef __ChargeTile_h__
#define __ChargeTile_h__

#include "Tile.h"

namespace jb
{

    class ChargeTile : public Tile
    {
    public:
        virtual bool canOccupy() const override { return true; }
        virtual bool isCharging() const override { return true; }
    };

}

#endif