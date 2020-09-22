#ifndef GAMELOGICTYPES_H
#define GAMELOGICTYPES_H

#include <common_pch.h>

using Position = std::pair<unsigned int, unsigned int>;
using Dimension2D = std::pair<unsigned int, unsigned int>;
using Identifier = int;
using CrossSpeed = unsigned int;
using ScoredPoint = unsigned int;

namespace kd417d
{
namespace eva
{
namespace logic
{
namespace bridge
{

enum struct BoardActionSet : int
{
    SELECT_TO_CROSS,
    DESELECT_TO_CROSS,
    CROSS,
    SELECT_TO_RETURN,
    DESELECT_TO_RETURN,
    RETURN
};

enum struct PlayerState : int
{
    CROSSING,
    RETURNING,
    ON_CROSSING_SIDE,
    ON_RETURNING_SIDE
};

enum struct PlayerType : int
{
    SLOW,
    MEDIUM,
    FAST
};

enum struct GameState : int
{
    CROSS_SELECTION,
    RETURN_SELECTION
};

enum struct PlayerActionSet : int
{
    MOVE_TO_BRIDGE,
    CROSS,
    RETURN
};

}
}
}
}

#endif // GAMELOGICTYPES_H
