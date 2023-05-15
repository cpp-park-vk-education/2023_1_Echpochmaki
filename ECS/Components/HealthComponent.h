//
// Created by Андрей on 04.05.2023.
//

#ifndef ECS_2023_1_ECHPOCHMAKI_ECS_COMPONENTS_HEALTHCOMPONRNT_H_
#define ECS_2023_1_ECHPOCHMAKI_ECS_COMPONENTS_HEALTHCOMPONRNT_H_

#include "../inc/ECS.h"
#include <SFML/Graphics.hpp>

using namespace sf;

using HealthValueType = int;

struct HealthComponent : public Component {
    HealthValueType health;

    HealthComponent() = default;

    HealthComponent(HealthValueType healthSrc) {
        health = healthSrc;
    }

};

#endif //ECS_2023_1_ECHPOCHMAKI_ECS_COMPONENTS_HEALTHCOMPONRNT_H_
