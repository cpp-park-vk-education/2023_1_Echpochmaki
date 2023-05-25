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

    static std::vector<Entity *> createEntitiesByMap(const tileMap &tilemap);

    static Entity *createEntity(const EntityTileBase &tile);

//    void *createRemotePlayer()

    static void packTileMap(const tileMap &tilemap, sf::Packet& pack);

    static void loadTileMap(sf::Packet& pack);

    static Entity *createPlayer(bool is_remote = false);
};

#endif //GAME_ENTITYCREATOR_H
