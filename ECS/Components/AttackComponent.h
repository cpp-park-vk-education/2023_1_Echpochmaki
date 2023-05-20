//
// Created by Андрей on 04.05.2023.
//

#ifndef ECS_2023_1_ECHPOCHMAKI_ECS_COMPONENTS_ATTACKCOMPONENT_H_
#define ECS_2023_1_ECHPOCHMAKI_ECS_COMPONENTS_ATTACKCOMPONENT_H_

#include "../inc/ECS.h"
#include <SFML/Graphics.hpp>

using namespace sf;

using DamageValueType = int;

static constexpr int DefaultAttackBoxSize = 50;

struct AttackComponent : public Component {
    DamageValueType damage;
    sf::IntRect attackBox;

    AttackComponent() = default;

    AttackComponent(DamageValueType damageSrc, sf::IntRect attackBoxSrc = {0, 0, DefaultAttackBoxSize, DefaultAttackBoxSize}) {
        damage = damageSrc;
        attackBox = attackBoxSrc;
    }


    bool attack_started;
};


#endif //ECS_2023_1_ECHPOCHMAKI_ECS_COMPONENTS_ATTACKCOMPONENT_H_
