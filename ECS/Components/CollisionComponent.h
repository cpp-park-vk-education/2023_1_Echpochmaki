//
// Created by Андрей on 04.05.2023.
//

#ifndef ECS_2023_1_ECHPOCHMAKI_ECS_COMPONENTS_COLLISIONCOMPONENT_H_
#define ECS_2023_1_ECHPOCHMAKI_ECS_COMPONENTS_COLLISIONCOMPONENT_H_

#include "../../inc/ECS.h"
#include <SFML/Graphics.hpp>

using namespace sf;

struct CollisionComponent : public Component {
    IntRect collisionBox;

    CollisionComponent() = default;

    CollisionComponent(const IntRect &collisionBoxSrc) {
        collisionBox = collisionBoxSrc;
    }


};


#endif //ECS_2023_1_ECHPOCHMAKI_ECS_COMPONENTS_COLLISIONCOMPONENT_H_
