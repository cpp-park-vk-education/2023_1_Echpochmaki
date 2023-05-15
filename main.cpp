#include <SFML/Graphics.hpp>

#include "Game.h"
#include "ECS/utils/FramesCreator.h"
#include "LevelManager.h"
//#include <cstdlib>

using namespace sf;

int main() {
    Game game(std::make_unique<LevelManager>(LevelManager()), std::make_unique<EntityManager>(EntityManager()));

    game.loadMap();

    game.run();
    return 0;
}
