#ifndef GAME_ANIMATIONMOVINGCOMPONENT_H
#define GAME_ANIMATIONMOVINGCOMPONENT_H

#include <vector>

#include <SFML/Graphics.hpp>
#include "../inc/ECS.h"

struct AnimationMovingComponent : Component {
    AnimationMovingComponent(std::vector<sf::Texture>& frames, sf::Texture& base_frame) : frames(frames),
    base_frame(base_frame)
    {
        size = frames.size();
        cur_frame = 0;
        animation_started = false;
    }

    std::vector<sf::Texture> frames;
    sf::Texture base_frame;
    size_t size;
    size_t cur_frame;

    bool animation_started;
};


#endif //GAME_ANIMATIONMOVINGCOMPONENT_H
