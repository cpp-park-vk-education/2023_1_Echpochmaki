#ifndef MAP_GENERATION_GAME_H
#define MAP_GENERATION_GAME_H

#include <memory>

#include "MapGeneration/inc/LevelManager.h"
#include "ECS/inc/EntityManager.h"
#include "net/inc/Network.h"

#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "EnemyComponent.h"
#include "PlayerComponent.h"
#include "SpriteComponent.h"

#include "DrawSystem.h"
#include "MoveSystem.h"
#include "PlayerSystem.h"
#include "HitBoxSystem.h"
#include "CameraSystem.h"

#include "Timer.h"


const int DELTA_TIME = 10.0;

class Game {
public:
    void loadMap();

    void run();

    void load(const char *config);

    explicit Game(std::unique_ptr<LevelManager> levelMgr) {
        level.swap(levelMgr);
    }

private:

    std::unique_ptr<LevelManager> level;
    std::unique_ptr<EntityManager> entityManager;
    std::unique_ptr<EntityCreator> entityCreator;
    std::unique_ptr<Network> network;
    sf::Window window;
};


#endif //MAP_GENERATION_GAME_H
