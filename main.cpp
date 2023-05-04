#include <animatable.h>
#include <SFML/Graphics.hpp>


using namespace sf;

int main()
{
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

	return 0;
}