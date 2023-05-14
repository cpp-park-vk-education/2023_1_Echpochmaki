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

	//Components
	EntityManager manager;
	Entity player;

	player.AddComponent<PositionComponent>();
	player.AddComponent<VelocityComponent>();
	player.AddComponent<PlayerComponent>();

	Image image;
	image.loadFromFile("../Graphics/textures/HeroKnight.png");
	Texture texture;
	texture.loadFromImage(image);
	Sprite sprite;
	sprite.setTexture(texture);
	sprite.setTextureRect(IntRect(0, 0, 100, 100));
	player.AddComponent<SpriteComponent>(sprite);
	manager.addEntity(&player);


	//Systems
	DrawSystem drawSystem;
	drawSystem.setRenderWindow(&window);
	manager.addSystem(&drawSystem);

	PlayerSystem playerSystem;
	manager.addSystem(&playerSystem);

	MoveSystem moveSystem;
	manager.addSystem(&moveSystem);







    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // TODO: Update frames
		//window.clear();
		window.draw(sprite);
		manager.update(this);

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
