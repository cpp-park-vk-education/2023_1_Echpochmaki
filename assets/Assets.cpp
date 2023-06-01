//
// Created by Повелитель on 31.05.2023.
//

#include "Assets.h"

std::map<std::string, std::pair<sf::Texture, sf::Image>> Assets::texCache;



void Assets::loadTextureFromFile(const std::string& path, sf::Texture& to_load, const sf::IntRect& area) {
    if (texCache.find(path) == texCache.end()) {
        sf::Texture tex;
        tex.loadFromFile(path);
        texCache.insert({ path, { tex, tex.copyToImage() } });
    }

    to_load.loadFromImage(texCache.find(path)->second.second, area);
}
