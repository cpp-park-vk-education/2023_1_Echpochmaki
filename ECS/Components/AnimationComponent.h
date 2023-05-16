//
// Created by Андрей on 03.05.2023.
//

#ifndef ECS_2023_1_ECHPOCHMAKI_ECS_ANIMATIONCOMPONENT_H_
#define ECS_2023_1_ECHPOCHMAKI_ECS_ANIMATIONCOMPONENT_H_

#include "ECS.h"
#include <SFML/Graphics.hpp>

using namespace sf;



struct Frame
{
    Frame(Texture& texture) : texture(texture), duration(1)
    {

    }
	IntRect rect;
    Texture texture;
	TimeValueType duration;
};





struct AnimationComponent : public Component
{

 public:
	std::vector<Frame> frames;
	Sprite *sprite;
    size_t current_frame;

	AnimationComponent() = delete;
	AnimationComponent(const std::vector<Frame> &framesSrc,Sprite &spriteSrc)
	{
		frames = framesSrc;
		sprite = &spriteSrc;
	}

    AnimationComponent(std::vector<Texture>& frames, Sprite &spriteSrc) : current_frame(0)
    {
        for (const auto& frame : frames)
        {
            frames.push_back(frame);
        }

        sprite = &spriteSrc;
    }

};

#endif //ECS_2023_1_ECHPOCHMAKI_ECS_ANIMATIONCOMPONENT_H_
