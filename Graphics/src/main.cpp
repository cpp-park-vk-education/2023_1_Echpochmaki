#include <animatable.h>
using namespace sf;

int main()
{
	RenderWindow window(sf::VideoMode(640, 480), "Nss");

	float CurrentFrame = 0;//хранит текущий кадр
	Clock clock;

	Player p("Graphics/textures/HeroKnight.png",250,250,72.0, 68.0);//создаем объект p класса player,задаем "hero.png" как имя файла+расширение, далее координата Х,У, ширина, высота.
	while (window.isOpen())
	{

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//0 - игрок , 1 - cундук


		///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////
		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {

			p.dir = -1; p.speed = 0.1;//dir =1 - направление вверх, speed =0.1 - скорость движения. Заметьте - время мы уже здесь ни на что не умножаем и нигде не используем каждый раз
			CurrentFrame += 0.01*time;
			if (CurrentFrame > 8) CurrentFrame -= 8;
			p.sprite.setTextureRect(IntRect(100 * int(CurrentFrame + 1),65, p.dir * 65, 45)); //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
		}

		if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
			p.dir = 1; p.speed = 0.1;//направление вправо, см выше
			CurrentFrame += 0.01*time;
			if (CurrentFrame > 8) CurrentFrame -= 8;
			p.sprite.setTextureRect(IntRect(100 * int(CurrentFrame),65, p.dir * 65, 45));  //через объект p класса player меняем спрайт, делая анимацию (используя оператор точку)
		}

		if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
			p.dir = 3; p.speed = 0.1;//направление вниз, см выше
			CurrentFrame += 0.01*time;
			if (CurrentFrame > 8) CurrentFrame -= 8;
			p.sprite.setTextureRect(IntRect(100 * int(CurrentFrame),65,  65, 45));

		}

		if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) { //если нажата клавиша стрелка влево или англ буква А
			p.dir = 2; p.speed = 0.1;//направление вверх, см выше
			CurrentFrame += 0.01*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (CurrentFrame > 8) CurrentFrame -= 8; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			p.sprite.setTextureRect(IntRect(100 * int(CurrentFrame),65,  65, 45));

		}

		p.update(time);//оживляем объект p класса Player с помощью времени sfml, передавая время в качестве параметра функции update. благодаря этому персонаж может двигаться


		window.clear();
		window.draw(p.sprite);//рисуем спрайт объекта p класса player
		window.display();
	}

	return 0;
}