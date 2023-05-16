//
// Created by Андрей on 04.05.2023.
//

#ifndef ECS_2023_1_ECHPOCHMAKI_ECS_COMPONENTS_ATTACKCOMPONENT_H_
#define ECS_2023_1_ECHPOCHMAKI_ECS_COMPONENTS_ATTACKCOMPONENT_H_

#include "../inc/ECS.h"
#include <SFML/Graphics.hpp>

using namespace sf;

using DamageValueType = int;

struct AttackComponent : public Component {
    DamageValueType damage;

    AttackComponent() = default;

    AttackComponent(DamageValueType damageSrc) {
        damage = damageSrc;
    }


    bool attack_started;
};


#endif //ECS_2023_1_ECHPOCHMAKI_ECS_COMPONENTS_ATTACKCOMPONENT_H_
