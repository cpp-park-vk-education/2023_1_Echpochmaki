//
// Created by Андрей on 03.05.2023.
//

#ifndef ECS_2023_1_ECHPOCHMAKI_ECS_POSITIONCOMPONENT_H_
#define ECS_2023_1_ECHPOCHMAKI_ECS_POSITIONCOMPONENT_H_

#include "../inc/ECS.h"
#include <SFML/Graphics.hpp>

using namespace sf;

using DistanceValueType = float;

struct PositionComponent : public Component {

public:
    Vector2<DistanceValueType> position;

    PositionComponent() = default;

    PositionComponent(const Vector2<DistanceValueType> &positionSrc) {
        position = positionSrc;
    }

    PositionComponent(DistanceValueType x, DistanceValueType y) {
        position.x = x;
        position.y = y;
    }

};

#endif //ECS_2023_1_ECHPOCHMAKI_ECS_POSITIONCOMPONENT_H_
