#ifndef __CmdUnknown_h__
#define __CmdUnknown_h__

#include "Cmd/Command.h"
#include "ExecuteResult.h"
#include <iostream>

namespace jb
{
    struct CmdUnknown : public Command
    {
        ExecuteResult execute(std::ostream& out) const override
        {
            out << "ERROR: Unknown command";
            return { ExecuteStatus::Blocked };
        }

        unsigned int getEnergyConsumption() const override
        {
            return 0;
        }
    } CMD_UNKNOWN;

}
#endif