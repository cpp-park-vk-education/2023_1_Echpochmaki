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

//    RenderWindow window(sf::VideoMode(640, 480), "Boys game");
    window.create(sf::VideoMode(640, 480), "Boys game");
    //window.setFramerateLimit(1.0f / DELTA_TIME);

    //Components
    Entity player;

    std::string hero_king_texture_path = "../Graphics/textures/HeroKnight.png";

    FramesCreator creator{hero_king_texture_path};
    auto frames = creator.GetFrames(9, 10, 14, 40, 0, 0);

    std::vector<sf::Texture> moving_frames{frames.begin() + 8, frames.begin() + 17};
    std::vector<sf::Texture> attack_frames{frames.begin() + 18, frames.begin() + 24};
    std::vector<sf::Texture> idling_frames{frames.begin() + 0, frames.begin() + 7};
    std::vector<sf::Texture> die_frames{frames.begin() + 49, frames.begin() + 57};


    std::vector<std::vector<sf::Texture>> all_frames;
    all_frames.push_back(moving_frames);
    all_frames.push_back(attack_frames);
    all_frames.push_back(idling_frames);


    player.AddComponent<PositionComponent>(200, 200);
    player.AddComponent<VelocityComponent>();
    player.AddComponent<PlayerComponent>();
    player.AddComponent<AttackComponent>(2);

    Sprite sprite;
    sprite.setTexture(frames[0]);

    player.AddComponent<SpriteComponent>(sprite, 100);
    player.AddComponent<CollisionComponent>(IntRect(0,0,30,40),Vector2<DistanceValueType>(30 / 2,40 / 2));
    player.AddComponent<MoveDirectionComponent>();
    player.AddComponent<FramesComponent>(all_frames, all_frames[0][0]);
    player.AddComponent<SinkableComponent>(random());
//    player.AddComponent<AttackAnimationComponent>(attack_frames, frames[0]);
//    player.AddComponent<AnimationMovingComponent>(moving_frames, frames[0]);


    entityManager->addEntity(&player);


    //Collider starts here
    Sprite collider;
    collider.setTexture(frames[0]);
    Entity testCollider;
    testCollider.AddComponent<PositionComponent>(0, 0);
    testCollider.AddComponent<CollisionComponent>(IntRect(0, 0, 60, 60));
    testCollider.AddComponent<SpriteComponent>(collider);

    entityManager->addEntity(&testCollider);

    //Systems
    DrawSystem drawSystem;
    drawSystem.setRenderWindow(&window);
    entityManager->addSystem(&drawSystem);

    PlayerSystem playerSystem;
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

//    AttackAnimationSystem attackAnimationSystem;

//    AnimateMovingDirectionSystem animateMovingDirectionSystem;
//    entityManager.addSystem(&animateMovingDirectionSystem);



    AttackSystem attackSystem;
    entityManager->addSystem(&attackSystem);

	FramesSystem framesSystem;
//    std::cout << "AddedFrameSystem" << std::endl;
	entityManager->addSystem(&framesSystem);

    RemoveSystem removeSystem;
    std::cout << "Added removeSystem status: " << entityManager->addSystem(&removeSystem);

    SyncSystem syncSystem;
    std::cout << "add syncSystem success=" << entityManager->addSystem(&syncSystem);

    std::cout << "entities size=" << entityManager->entities.size() << std::endl;
    int id = 0;
    for (auto &e : entityManager->entities)
    {
        e->id = Entity::nextId();
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
