#ifndef GAME_ENTITYTILEBASE_H
#define GAME_ENTITYTILEBASE_H

#include <vector>

struct EntityTileBase {
    int objectId;

    constexpr explicit EntityTileBase(int id) : objectId(id) {};
};

inline const int tileWidth = 60;
inline const int tileHeight = 60;

inline constexpr EntityTileBase floorTile(0);
inline constexpr EntityTileBase wallTile(1);
inline constexpr EntityTileBase doorTile(2);

inline constexpr EntityTileBase enemyTile(3);

using tileMap = std::vector<std::vector<EntityTileBase>>;

#endif //GAME_ENTITYTILEBASE_H
