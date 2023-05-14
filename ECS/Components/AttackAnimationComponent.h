#ifndef GAME_ATTACKANIMATIONCOMPONENT_H
#define GAME_ATTACKANIMATIONCOMPONENT_H


#include <SFML/Graphics.hpp>
#include <vector>
#include "ECS.h"

struct AttackAnimationComponent : public Component{
    AttackAnimationComponent(std::vector<sf::Texture>& frames, sf::Texture base_frame) : frames(frames),
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

#endif //GAME_ATTACKANIMATIONCOMPONENT_H
