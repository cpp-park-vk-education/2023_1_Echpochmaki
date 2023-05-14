#ifndef GAME_ENTITYTILEBASE_H
#define GAME_ENTITYTILEBASE_H

#include <vector>

struct EntityTileBase {
    int objectId;
};

inline const EntityTileBase floorTile = {0};
inline const EntityTileBase wallTile = {1};
inline const EntityTileBase doorTile = {2};

inline const EntityTileBase enemyTile = {3};

using tileMap = std::vector<std::vector<EntityTileBase>>;

#endif //GAME_ENTITYTILEBASE_H
