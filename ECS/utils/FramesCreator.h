#ifndef GAME_FRAMESCREATOR_H
#define GAME_FRAMESCREATOR_H

#include <SFML/Graphics.hpp>
#include <iostream>

class FramesCreator {
public:
    explicit FramesCreator(std::string &filepath_) : filepath(filepath_) {
        //texture.getSize();
    }

    FramesCreator() = default;

    void setFilePath(std::string &filepath_) {
        filepath = filepath_;
    }

    std::vector<sf::Texture> GetFrames(size_t rows, size_t cols) {
        sf::Texture texture;
        texture.loadFromFile(filepath);
        auto size = texture.getSize();
        std::vector<sf::Texture> frames;
        size_t width_frame = size.x / cols;
        size_t height_frame = size.y / rows;
        //std::cout << size.x << std::endl;
        //std::cout << size.y << std::endl;

        for (size_t i = 0; i < rows; ++i) {
            for (size_t j = 0; j < cols; ++j) {
                sf::Texture frame;
                frame.loadFromFile(filepath, sf::IntRect(j * width_frame, i * height_frame, width_frame, height_frame));
                //std::cout << j * width_frame << " " << i * height_frame << " " << width_frame << " " << height_frame
                //        << std::endl;
                frames.push_back(frame);
            }
        }

        return frames;
    }

protected:
    std::string filepath;
};


#endif //GAME_FRAMESCREATOR_H
