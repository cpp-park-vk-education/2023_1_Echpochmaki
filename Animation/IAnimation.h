//
// Created by Андрей on 03.05.2023.
//

#ifndef ECS_2023_1_ECHPOCHMAKI_ANIMATION_IANIMATION_H_
#define ECS_2023_1_ECHPOCHMAKI_ANIMATION_IANIMATION_H_


#include <SFML/Graphics.hpp>

using namespace sf;

using TimeValueType = double;

struct Frame
{
	IntRect rect;
	TimeValueType duration;

	Frame(IntRect rect_fr,TimeValueType duration_fr)
	{
		rect = rect_fr;
		duration = duration_fr;
	}
};


class IAnimation
{
	virtual void addFrame(const Frame &frame) = 0;
	virtual void update(TimeValueType timPassed) = 0;
};

#endif //ECS_2023_1_ECHPOCHMAKI_ANIMATION_IANIMATION_H_
