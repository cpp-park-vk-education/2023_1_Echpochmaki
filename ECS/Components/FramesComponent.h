#ifndef GAME_FRAMESCOMPONENT_H
#define GAME_FRAMESCOMPONENT_H

#include <SFML/Graphics.hpp>
#include "../inc/ECS.h"


enum class FrameSet
{
    MOVE = 0,
    ATTACK = 1,
	IDLE = 2,
    DIE = 3
};

struct FramesComponent : public Component {
    FramesComponent(std::vector<std::vector<sf::Texture>>& frames_sets, sf::Texture& base_frame) : frames_sets(frames_sets),
                                                                                          base_frame(base_frame), passed_time(0)
    {
        frame_sets_size = frames_sets.size();
        cur_frame = 0;
        animation_started = false;
    }

    std::vector<std::vector<sf::Texture>> frames_sets;
    sf::Texture base_frame;
    size_t frame_sets_size;
    size_t cur_frame;
    FrameSet cur_frame_set;
	double passed_time;
    bool animation_started;
    bool died = false;
    bool dying = false;
};

#endif //GAME_FRAMESCOMPONENT_H
