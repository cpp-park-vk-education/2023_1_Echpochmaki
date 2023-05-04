#ifndef MAP_GENERATION_GAME_H
#define MAP_GENERATION_GAME_H

#include <memory>

#include "map_generation/LevelManager.h"
#include "ECS/EntityManager.h"
#include "net/Network.hpp"


class Game {
public:
    void getMap();
    void run();
    void load(const char *config);

private:
    tileMap map;

    std::unique_ptr<LevelManager> level;
    std::unique_ptr<EntityManager> entity;
    std::unique_ptr<Network> network;
};


#endif //MAP_GENERATION_GAME_H
