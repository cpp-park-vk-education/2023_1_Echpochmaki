//
// Created by Андрей on 04.05.2023.
//

#ifndef ECS_2023_1_ECHPOCHMAKI_ECS_COMPONENTS_VELOCITYCOMPONENT_H_
#define ECS_2023_1_ECHPOCHMAKI_ECS_COMPONENTS_VELOCITYCOMPONENT_H_

#include "../inc/ECS.h"
#include <SFML/Graphics.hpp>

using namespace sf;

using DistanceValueType = float;

struct VelocityComponent : public Component {

public:
    Vector2<DistanceValueType> velocity;
    Vector2<DistanceValueType> default_velocity;

    VelocityComponent() = default;

    VelocityComponent(const Vector2<DistanceValueType> &velocitySrc) {
        velocity = velocitySrc;
        default_velocity = velocity;
    }

    VelocityComponent(DistanceValueType x, DistanceValueType y) {
        velocity.x = x;
        default_velocity.x = x;

        velocity.y = y;
        default_velocity.y = y;
    }

};

#endif //ECS_2023_1_ECHPOCHMAKI_ECS_COMPONENTS_VELOCITYCOMPONENT_H_
