//
// Created by Андрей on 04.05.2023.
//

#ifndef ECS_2023_1_ECHPOCHMAKI_ECS_COMPONENTS_COLLISIONCOMPONENT_H_
#define ECS_2023_1_ECHPOCHMAKI_ECS_COMPONENTS_COLLISIONCOMPONENT_H_

#include "../inc/ECS.h"
#include <SFML/Graphics.hpp>

using namespace sf;

using DistanceValueType = float;

struct CollisionComponent : public Component {
    IntRect collisionBox;
	Vector2<DistanceValueType> offset;

    CollisionComponent() = default;

    CollisionComponent(const IntRect &collisionBoxSrc,const Vector2<DistanceValueType> & offsetSrc = {0,0}) {
        collisionBox = collisionBoxSrc;
		offset = offsetSrc;

    }


};


#endif //ECS_2023_1_ECHPOCHMAKI_ECS_COMPONENTS_COLLISIONCOMPONENT_H_
