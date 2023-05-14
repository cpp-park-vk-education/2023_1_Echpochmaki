#include <animatable.h>
#include <SFML/Graphics.hpp>

#include "Game.h"
#include "ECS/utils/FramesCreator.h"
//#include <cstdlib>

using namespace sf;

int main()
{
    std::string filename = "../Tiles1.png";
    sf::Texture texture;
    //texture.loadFromFile("../Tiles.png");
    //sf::Sprite sprite;
    //sprite.setTexture(texture);

    FramesCreator creator{filename};
    std::vector<sf::Texture> frames = creator.GetFrames(6, 7);
    sf::RenderWindow window(sf::VideoMode(500, 500), "Kek");
    sf::Sprite sprite;
    sprite.setScale(10, 10);
    sprite.setTexture(frames[1]);
    sf::Texture texture1;
//    texture1.loadFromFile("../Tiles.png", sf::IntRect(0, 0, 16, 18));
//    sprite.setTexture(texture1);
    window.clear();

    window.draw(sprite);
    while (true)
    {
        window.display();
    }

    //std::system("ls -al");
	//Game game;
	//game.run();
	return 0;
}
