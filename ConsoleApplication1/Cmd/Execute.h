#ifndef __CmdExecute_h__
#define __CmdExecute_h__

#include <functional>
#include <ostream>
#include "Cmd/Command.h"

namespace jb
{

    class CmdExecute : public Command
    {
    public:
        CmdExecute(const std::function<void(std::ostream&)>& toExecute)
            : m_toExecute(toExecute) {
        }

        CmdExecute(std::function<void(std::ostream&)>&& toExecute)
            : m_toExecute(std::move(toExecute)) {
        }

        virtual ExecuteResult execute(std::ostream& out) const override;

    private:
        std::function<void(std::ostream&)> m_toExecute;
    };

}

#endif