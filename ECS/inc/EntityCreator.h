//
// Created by User on 15.05.2023.
//

#ifndef GAME_ENTITYCREATOR_H
#define GAME_ENTITYCREATOR_H

#include "Tile.h"
#include "ECS.h"

class EntityCreator {
public:
    std::vector<Entity *> createEntitiesByMap(const tileMap &tilemap);

    Entity *createEntity(const EntityTileBase &tile);
};

#endif //GAME_ENTITYCREATOR_H
