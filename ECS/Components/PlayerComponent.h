//
// Created by Андрей on 14.05.2023.
//

#ifndef GAME_2023_1_ECHPOCHMAKI_ECS_COMPONENTS_PLAYERCOMPONENT_H_
#define GAME_2023_1_ECHPOCHMAKI_ECS_COMPONENTS_PLAYERCOMPONENT_H_

#include "ECS.h"
#include <SFML/Graphics.hpp>

using namespace sf;

using TypeId = int;

using DistanceValueType = float;

struct PlayerComponent : public Component
{
	TypeId Id;
	DistanceValueType speed;




};

#endif //GAME_2023_1_ECHPOCHMAKI_ECS_COMPONENTS_PLAYERCOMPONENT_H_
