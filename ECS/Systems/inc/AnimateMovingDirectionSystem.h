#ifndef GAME_ANIMATEMOVINGDIRECTIONSYSTEM_H
#define GAME_ANIMATEMOVINGDIRECTIONSYSTEM_H

#include "../inc/EntityManager.h"
#include "AnimationMovingComponent.h"
#include "SpriteComponent.h"
#include "BaseSystem.h"

//using TypeId = size_t;

constexpr TypeId MovingID = 123456;


class AnimateMovingDirectionSystem : public BaseSystem {
    int getSystemID() override {
        return MovingID;
    }

    void update(EntityManager *manager) override {
        std::vector<Entity*> entities;

        manager->selectEntites<AnimationMovingComponent>(entities);

        std::cout << "ANIME: " << entities.size() << std::endl;
        std::cout << "ANIME: " << entities.size() << std::endl;
        std::cout << "ANIME: " << entities.size() << std::endl;
        std::cout << "ANIME: " << entities.size() << std::endl;
        std::cout << "ANIME: " << entities.size() << std::endl;

        for (auto entity: entities)
        {
            auto &move = entity->getComponent<AnimationMovingComponent>();
            auto &attack = entity->getComponent<AttackAnimationComponent>();

            if (move.animation_started)
            {
                if (!attack.animation_started) {

                    auto &sprite = entity->getComponent<SpriteComponent>();
                    sprite.sprite.setTexture(
                            move.frames[move.cur_frame++]); // возможно стоит сбросить ректангл, подумать!!

                    if (move.cur_frame >= move.size) {
                        move.cur_frame = 0;
                        move.animation_started = false;
                    }
                }
                else
                {
                    move.animation_started = false;
                }
            }
            else
            {
                auto &sprite = entity->getComponent<SpriteComponent>();
                sprite.sprite.setTexture(move.base_frame);
                std::cout << "aboba" << std::endl;
            }
        }
    }

    bool added() override
    {
        return true;
    }//TODO::find out what to return
};

#endif //GAME_ANIMATEMOVINGDIRECTIONSYSTEM_H
