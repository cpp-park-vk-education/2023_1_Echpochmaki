#ifndef GAME_ENEMYCOMPONENT_H
#define GAME_ENEMYCOMPONENT_H

#include "ECS.h"
#include <SFML/Graphics.hpp>

using TypeId = int;

struct EnemyComponent : public Component
{
    TypeId id;

    HealthComponent() = default;

    HealthComponent(HealthValueType healthSrc)
    {
        health = healthSrc;
    }

    TypeId GetId() const
    {
        return id;
    }
};

#endif //GAME_ENEMYCOMPONENT_H
