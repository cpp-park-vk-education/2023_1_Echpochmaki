//
// Created by Андрей on 04.05.2023.
//

#ifndef ECS_2023_1_ECHPOCHMAKI_ECS_COMPONENTS_TARGETCOMPONENT_H_
#define ECS_2023_1_ECHPOCHMAKI_ECS_COMPONENTS_TARGETCOMPONENT_H_

#include "ECS.h"
#include <SFML/Graphics.hpp>

using namespace sf;

struct TargetComponent : public Component
{

 public:
	 int targetID;

	TargetComponent() = default;

	TargetComponent(int targetIDSrc)
	{
		 targetID = targetIDSrc;
	}

};

#endif //ECS_2023_1_ECHPOCHMAKI_ECS_COMPONENTS_TARGETCOMPONENT_H_
