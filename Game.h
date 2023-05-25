#ifndef MAP_GENERATION_GAME_H
#define MAP_GENERATION_GAME_H

#include <memory>

#include "MapGeneration/inc/LevelManager.h"
#include "ECS/inc/EntityManager.h"
#include "ECS/inc/EntityCreator.h"

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

    explicit Game(std::unique_ptr<LevelManager> levelMgr, std::unique_ptr<EntityManager> entityMgr) {
        level.swap(levelMgr);
        entityManager.swap(entityMgr);
        network = std::make_unique<Network>();

        instance = this;
    }

    static Game *GetInstance()
    {
        return Game::instance;
    }

	std::unique_ptr<EntityManager> entityManager;
public:

    std::unique_ptr<LevelManager> level;

    std::unique_ptr<EntityCreator> entityCreator;
    std::unique_ptr<Network> network;
    sf::RenderWindow window;

    static Game *instance;
    tileMap map;
};


#endif //MAP_GENERATION_GAME_H
