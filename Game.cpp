#include "Game.h"
#include "EnemySystem.h"
#include "AnimateDirectionSystem.h"
#include "AttackAnimationSystem.h"
#include "ECS/utils/FramesCreator.h"
#include "AnimationMovingComponent.h"
#include "AnimateMovingDirectionSystem.h"
#include "FramesSystem.h"
#include "AttackSystem.h"
#include "RemoveEntitySystem.h"
#include "SinkableComponent.h"
#include "RenderInfoSystem.h"
#include "SyncSystem.h"

Game *Game::instance;

void Game::loadMap() {
    // Получение карты, передача Entity Creator
    // map -> EntityCreator -> (vector <Entity>) -> EntityManager
    auto map = level->createMap();
    auto entities = entityCreator->createEntitiesByMap(map);
    for (auto entity: entities) {
        entityManager->addEntity(entity);
    }
}

void Game::load(const char *config) {
    // Загрузка конфига
}

void Game::run() {
    // Loop обновление по кадрам всего

//    RenderWindow window(sf::VideoMode(1280, 1024), "Boys game");
    window.create(sf::VideoMode(640, 480), "Boys game");
    //window.setFramerateLimit(60);

//	window.setVerticalSyncEnabled(true);

    //Components
    std::string path_to_main_font = "./Graphics/fonts/main_font.ttf";
    

    //Systems
    DrawSystem drawSystem;
    drawSystem.setRenderWindow(&window);
    entityManager->addSystem(&drawSystem);

    PlayerSystem playerSystem;
    playerSystem.setWindow(&window);
    entityManager->addSystem(&playerSystem);

    MoveSystem moveSystem;
    entityManager->addSystem(&moveSystem);

    EnemySystem enemy_system;
    entityManager->addSystem(&enemy_system);

    AnimateDirectionSystem animateDirectionSystem;
    entityManager->addSystem(&animateDirectionSystem);


    CameraSystem cameraSystem;
    cameraSystem.setRenderWindow(&window);
    entityManager->addSystem(&cameraSystem);

    RenderInfoSystem renderInfoSystem{&window, path_to_main_font};
    entityManager->addSystem(&renderInfoSystem);


//    AttackAnimationSystem attackAnimationSystem;

//    AnimateMovingDirectionSystem animateMovingDirectionSystem;
//    entityManager.addSystem(&animateMovingDirectionSystem);

    RemoveSystem removeSystem;
    entityManager->addSystem(&removeSystem);

    AttackSystem attackSystem;
    entityManager->addSystem(&attackSystem);

    FramesSystem framesSystem;
    entityManager->addSystem(&framesSystem);

    SyncSystem syncSystem;
    std::cout << "add syncSystem success=" << entityManager->addSystem(&syncSystem);

    std::cout << "entities size=" << entityManager->entities.size() << std::endl;
    int id = 0;
    for (auto &e: entityManager->entities) {
//        e->id = Entity::nextId();
//        std::cout << "e: " << e->id << std::endl;
    }


    char variant;
    std::cout << "choose 'h' for host and 'c' for client, 's' for single-player: ";
    std::cin >> variant;

    if (variant == 'h')
        network->runHost();
    else if (variant == 'c')
        network->connectToHost("localhost", Network::HOST_PORT);


    while (window.isOpen()) {
        //std::cout << "update " << random() % 10 << std::endl;
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized) {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
        }

        // TODO: Update frames
        window.clear();

        network->update();

        entityManager->update(this);

        window.display();
    }
    /*RenderWindow Window(VideoMode(600, 600), "Pong");

    // Объект;
    Image Player;
    // Загружаем в него файл;
    Player.loadFromFile("hero.png");

    // Текстура;
    Texture Player_texture;
    // Передаем в него объект 'Image';
    Player_texture.loadFromImage(Player);

    // Спрайт
    Sprite Player_sprite;
    // Передаем в него оюъект текстуры;
    Player_sprite.setTexture(Player_texture);
    // Определенные координаты из картинки;
    Player_sprite.setTextureRect(IntRect(0, 192, 96, 96));
    // Начальные координаты появления спрайта;
    Player_sprite.setPosition(50, 25);


    //Главный цикл приложения;
    while (Window.isOpen())
    {
        // Обработка событий в цикле;
        Event Event;

        while (Window.pollEvent(Event))
        {
            if (Event.type == sf::Event::Closed) { Window.close(); };
        };

        // X,Y; Идем вверх;
        if (Keyboard::isKeyPressed(Keyboard::W)) { Player_sprite.move(0, -0.1); Player_sprite.setTextureRect(IntRect(0, 288, 96, 96)); };
        // Идем вниз;
        if (Keyboard::isKeyPressed(Keyboard::S)) { Player_sprite.move(0, 0.1); Player_sprite.setTextureRect(IntRect(0, 0, 96, 96)); };
        // Идем влево;
        if (Keyboard::isKeyPressed(Keyboard::A)) { Player_sprite.move(-0.1, 0); Player_sprite.setTextureRect(IntRect(0, 96, 96, 96)); };
        // Идем вправо;
        if (Keyboard::isKeyPressed(Keyboard::D)) { Player_sprite.move(0, 0.1); Player_sprite.setTextureRect(IntRect(0, 0, 96, 96)); };


        // Очистка;
        Window.clear();
        // Рисуем спрайт;
        Window.draw(Player_sprite);


        // Отрисовка;
        Window.display();
    };*/

}
