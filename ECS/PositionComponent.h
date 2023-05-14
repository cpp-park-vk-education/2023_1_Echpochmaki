//
// Created by Андрей on 03.05.2023.
//

#ifndef ECS_2023_1_ECHPOCHMAKI_ECS_POSITIONCOMPONENT_H_
#define ECS_2023_1_ECHPOCHMAKI_ECS_POSITIONCOMPONENT_H_

#include "ECS.h"
#include <SFML/Graphics.hpp>

using namespace sf;

using DistanceValueType = float;

class PositionComponent : public Component
{

 private:
	Vector2<DistanceValueType> position;


 public:
	PositionComponent() = default;


	void Init() override
	{
		position = sf::Vector2<DistanceValueType>();
	}
	void Update(TimeValueType timePassed) override
	{
		//TODO::Make move implementable for all classes
	}
	void SetPosition(DistanceValueType x, DistanceValueType y)
	{
		position = sf::Vector2<DistanceValueType>(x,y);
	}
	void SetPosition(const sf::Vector2<DistanceValueType> &NewPosition)
	{
		position = NewPosition;
	}
	Vector2<DistanceValueType> GetPosition()
	{
		return position;
	}
};


#endif //ECS_2023_1_ECHPOCHMAKI_ECS_POSITIONCOMPONENT_H_
