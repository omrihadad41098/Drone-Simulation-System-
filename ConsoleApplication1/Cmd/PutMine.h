#ifndef PUT_MINE_H
#define PUT_MINE_H

#include "Cmd/Command.h"
#include "MineManager.h"
#include "Position.h"

#include <cstddef>
#include <ostream>

namespace jb
{

    class CmdPutMine : public Command
    {
    public:
        CmdPutMine(MineManager& mineManager,
            const Position& dronePosition,
            size_t droneId,
            size_t& minesLeft);

        virtual ExecuteResult execute(std::ostream& out) const override;

    private:
        MineManager& m_mineManager;
        const Position& m_dronePosition;
        size_t m_droneId;
        size_t& m_minesLeft;
    };

}

#endif