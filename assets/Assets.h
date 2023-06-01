//
// Created by Повелитель on 31.05.2023.
//

#ifndef GAME_ASSETS_H
#define GAME_ASSETS_H


#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class Assets {
public:

    static void loadTextureFromFile(const std::string& path, sf::Texture& to_load, const sf::IntRect& area = sf::IntRect());

private:
    static std::map<std::string, std::pair<sf::Texture, sf::Image>> texCache;

};


#endif //GAME_ASSETS_H
