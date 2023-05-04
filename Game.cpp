#include "Game.h"

void Game::loadMap(){
    // Получение карты, передача Entity Creator
    // map -> EntityCreator -> (vector <Entity>) -> EntityManager
    map = level->createMap();
    auto entities = entityCreator->createEntitiesByMap(map);
    entityManager->setEntities(std::move(entities));
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

        // TODO: Update frames
    }
}
