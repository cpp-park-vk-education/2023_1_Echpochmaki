#ifndef GAME_MOVEDIRECTIONCOMPONENT_H
#define GAME_MOVEDIRECTIONCOMPONENT_H

#include "../inc/ECS.h"

enum class Direction {
    LEFT = 0,
    RIGHT = 1
};

struct MoveDirectionComponent : public Component {
    Direction dir = Direction::RIGHT;
    bool has_dir_changed;
};

#endif //GAME_MOVEDIRECTIONCOMPONENT_H
