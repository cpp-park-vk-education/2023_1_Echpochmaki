#ifndef GAME_ENTITYTILEBASE_H
#define GAME_ENTITYTILEBASE_H

#include <vector>

struct EntityTileBase {
    int objectId;
};

using tileMap = std::vector<std::vector<EntityTileBase>>;

#endif //GAME_ENTITYTILEBASE_H
