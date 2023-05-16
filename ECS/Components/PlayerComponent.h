//
// Created by Андрей on 14.05.2023.
//

#ifndef GAME_2023_1_ECHPOCHMAKI_ECS_COMPONENTS_PLAYERCOMPONENT_H_
#define GAME_2023_1_ECHPOCHMAKI_ECS_COMPONENTS_PLAYERCOMPONENT_H_

#include "../inc/ECS.h"
#include <SFML/Graphics.hpp>

using namespace sf;

using TypeId = int;

using DistanceValueType = float;

const float defaultSpeed = 15;


struct PlayerComponent : public Component {
    TypeId Id;
    DistanceValueType speed;
    size_t kills = 0;

    PlayerComponent() {
        speed = defaultSpeed;
        Id = 0;
    }

    explicit PlayerComponent(TypeId id) : PlayerComponent()
    {
        Id = id;
    }


};

#endif //GAME_2023_1_ECHPOCHMAKI_ECS_COMPONENTS_PLAYERCOMPONENT_H_
