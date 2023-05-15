#include <SFML/Graphics.hpp>

#include "Game.h"
#include "ECS/utils/FramesCreator.h"
#include "LevelManager.h"
//#include <cstdlib>

using namespace sf;

int main() {
    Game game(std::make_unique<LevelManager>(LevelManager()));
    game.run();
    return 0;
}
