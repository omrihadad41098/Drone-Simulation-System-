#ifndef EXECUTERESULT_H
#define EXECUTERESULT_H

#include <cstddef>
#include <optional>
#include <vector>

namespace jb
{
    enum class ExecuteStatus
    {
        Success,
        Blocked,
        Collision
    };

    struct ExecuteResult
    {
        ExecuteStatus status;
        std::optional<std::size_t> otherDroneId = std::nullopt;
        std::vector<size_t> deadDroneIds;
    };
}

#endif