#ifndef MAP_GENERATION_GAME_H
#define MAP_GENERATION_GAME_H

#include <memory>

#include "map_generation/LevelManager.h"
#include "ECS/EntityManager.h"
#include "net/Network.hpp"

#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "EnemyComponent.h"
#include "PlayerComponent.h"
#include "SpriteComponent.h"

#include "DrawSystem.h"
#include "MoveSystem.h"
#include "PlayerSystem.h"
#include "HitBoxSystem.h"


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
