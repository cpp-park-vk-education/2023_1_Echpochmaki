#ifndef MAP_GENERATION_GAME_H
#define MAP_GENERATION_GAME_H

#include <memory>

#include "MapGeneration/inc/LevelManager.h"
#include "ECS/inc/EntityManager.h"
#include "net/inc/Network.hpp"


class Game {
public:
    void loadMap();

    void run();

    void load(const char *config);

private:
    tileMap map;

    std::unique_ptr<LevelManager> level;
    std::unique_ptr<EntityManager> entityManager;
    std::unique_ptr<EntityCreator> entityCreator;
    std::unique_ptr<Network> network;
};


#endif //MAP_GENERATION_GAME_H
