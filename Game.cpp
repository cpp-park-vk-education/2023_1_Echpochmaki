#include "Game.h"

void Game::loadMap(){
    // Получение карты, передача Entity Creator
    map = level->createMap();
    // map -> EntityCreator -> (vector <Entity>) -> EntityManager
}

void Game::load(const char *config) {
    // Загрузка конфига
}

void Game::run() {
    // Loop обновление по кадрам всего
    RenderWindow window(sf::VideoMode(640, 480), "Nss");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
}
