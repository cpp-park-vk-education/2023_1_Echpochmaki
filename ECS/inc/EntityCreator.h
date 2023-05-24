//
// Created by User on 15.05.2023.
//

#ifndef GAME_ENTITYCREATOR_H
#define GAME_ENTITYCREATOR_H

#include "Tile.h"
#include "ECS.h"

#ifndef INFO
#define INFO __FILE__ << ":" << __LINE__
#endif


class EntityCreator {
public:
    EntityCreator()
    {
        std::cout << "[entitycreator] " << INFO << " instance created" << std::endl;
    }

    std::vector<Entity *> createEntitiesByMap(const tileMap &tilemap);

    Entity *createEntity(const EntityTileBase &tile);
};

#endif //GAME_ENTITYCREATOR_H
