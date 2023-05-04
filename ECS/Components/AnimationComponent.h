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
	IntRect rect;
	TimeValueType duration;
};





struct AnimationComponent : public Component
{

 public:
	std::vector<Frame> frames;
	Sprite *sprite;

	AnimationComponent() = default;
	AnimationComponent(const std::vector<Frame> &framesSrc,Sprite &spriteSrc)
	{
		frames = framesSrc;
		sprite = &spriteSrc;
	}



};

#endif //ECS_2023_1_ECHPOCHMAKI_ECS_ANIMATIONCOMPONENT_H_
