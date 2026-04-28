#include "PutMine.h"

namespace jb
{

    CmdPutMine::CmdPutMine(MineManager& mineManager,
        const Position& dronePosition,
        size_t droneId,
        size_t& minesLeft)
        : m_mineManager(mineManager),
        m_dronePosition(dronePosition),
        m_droneId(droneId),
        m_minesLeft(minesLeft)
    {
    }

    ExecuteResult CmdPutMine::execute(std::ostream& out) const
    {
        if (m_minesLeft == 0)
        {
            out << "no mines left\n";
            return { ExecuteStatus::Blocked };
        }

        m_mineManager.addMine(m_droneId, m_dronePosition);
        --m_minesLeft;

        out << "mine placed. mines left: " << m_minesLeft  << "\n";

        return { ExecuteStatus::Success };
    }

}