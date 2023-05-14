#include "AttackAnimationComponent.h"
#include "BaseSystem.h"
#include "../../inc/EntityManager.h"
#include "SpriteComponent.h"

//using TypeId = size_t;

constexpr TypeId AttackID = 383962;




class AttackAnimationSystem : public BaseSystem
{
    int getSystemID() override
    {
        return AttackID;
    }

    void update(EntityManager* manager) override
    {
        std::vector<Entity*> entities;

        manager->selectEntites<AttackAnimationComponent>(entities);

        for (auto entity: entities)
        {
            auto& attack = entity->getComponent<AttackAnimationComponent>();

            if (attack.animation_started)
            {
                auto& sprite = entity->getComponent<SpriteComponent>();
                sprite.sprite.setTexture(attack.frames[attack.cur_frame++]); // возможно стоит сбросить ректангл, подумать!!

                if (attack.cur_frame >= attack.size)
                {
                    attack.cur_frame = 0;
                    attack.animation_started = false;
                }
            }
            else
            {
                auto& sprite = entity->getComponent<SpriteComponent>();
                sprite.sprite.setTexture(attack.base_frame);
                std::cout << "aboba" << std::endl;
            }
        }
    }

    bool added() override
    {
        return true;
    }//TODO::find out what to return

};


#ifndef GAME_ATTACKANIMATIONSYSTEM_H
#define GAME_ATTACKANIMATIONSYSTEM_H

#endif //GAME_ATTACKANIMATIONSYSTEM_H
