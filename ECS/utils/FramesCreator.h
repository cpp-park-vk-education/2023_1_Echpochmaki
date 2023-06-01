#ifndef GAME_FRAMESCREATOR_H
#define GAME_FRAMESCREATOR_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "assets/Assets.h"

class FramesCreator {
public:
    FramesCreator(std::string &filepath) : filepath(filepath) {
        //texture.getSize();
    }

    std::vector<sf::Texture> GetFrames(size_t rows, size_t cols, size_t margin_left, size_t margin_right,
                                       size_t margin_top, size_t margin_bottom) {
        sf::Texture texture;
        Assets::loadTextureFromFile(filepath, texture);
//        texture.loadFromFile(filepath);
        auto size = texture.getSize();
        std::vector<sf::Texture> frames;
        size_t width_frame = size.x / cols;
        size_t height_frame = size.y / rows;
        //std::cout << size.x << std::endl;
        //std::cout << size.y << std::endl;

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                sf::Texture frame;
//                Assets::loadTextureFromFile(filepath, texture, sf::IntRect(j * width_frame + margin_left, i * height_frame + margin_top,
//                                                         width_frame - margin_right, height_frame - margin_bottom));

                frame.loadFromFile(filepath, sf::IntRect(j * width_frame + margin_left, i * height_frame + margin_top,
                                                         width_frame - margin_right, height_frame - margin_bottom));
                // std::cout << j * width_frame << " " << i * height_frame << " " << width_frame  << " " << height_frame << std::endl;
                frames.push_back(frame);
            }
        }

        return frames;
    }

//    std::vector<sf::Texture> GetResized(std::vector<sf::Texture>& textures)
//    {
//        std::vector<sf::Texture> res;
//
//        for (auto& texture: textures)
//        {
//            sf::Texture temp;
//            //temp.
//            //res.push_back()
//        }
//
//    }


protected:
    std::string filepath;
};


#endif //GAME_FRAMESCREATOR_H
