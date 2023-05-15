#ifndef GAME_FRAMESSYSTEM_H
#define GAME_FRAMESSYSTEM_H


#include "../inc/EntityManager.h"
#include "FramesComponent.h"
#include "SpriteComponent.h"
#include "BaseSystem.h"

//using TypeId = size_t;

constexpr TypeId FramesSystemID = 13245096;
constexpr double FrameTimeDelta = 1;


class FramesSystem : public BaseSystem {
    int getSystemID() override {
        return MovingID;
    }

    void update(EntityManager *manager) override {
        std::vector<Entity *> entities;

        manager->selectEntites<FramesComponent>(entities);

//        std::cout << "FRAMES: " << entities.size() << std::endl;
//        std::cout << "FRAMES: " << entities.size() << std::endl;
//        std::cout << "FRAMES: " << entities.size() << std::endl;
//        std::cout << "FRAMES: " << entities.size() << std::endl;
//        std::cout << "FRAMES: " << entities.size() << std::endl;

        for (auto entity: entities) {
            auto &framesComponent = entity->getComponent<FramesComponent>();
            // std::cout << "Frame System cycle started" << std::endl;
            //auto &move = entity->getComponent<AnimationMovingComponent>();
            //auto &attack = entity->getComponent<AttackAnimationComponent>();

            if (framesComponent.animation_started) {
                if (framesComponent.cur_frame >=
                    framesComponent.frames_sets[static_cast<unsigned long>(framesComponent.cur_frame_set)].size()) {
                        framesComponent.cur_frame = 0;
                        framesComponent.animation_started = false;
                        continue;
                }
				framesComponent.passed_time += Timer::getTimer().getElapsedTime().asMicroseconds(); //TODO::fix const values for frames

				//std::cout << "passed_time" <<  framesComponent.passed_time << '\n';
				//Timer::getTimer().restart();
				if (int(framesComponent.passed_time) > FrameTimeDelta)
				{
					auto& sprite = entity->getComponent<SpriteComponent>();
					sprite.sprite.setTexture(
						framesComponent.frames_sets[static_cast<unsigned long>(framesComponent.cur_frame_set)][framesComponent.cur_frame++]); // возможно стоит сбросить ректангл, подумать!!
					framesComponent.passed_time = 0;
					Timer::getTimer().restart();
				}

            }
            else
            {
				framesComponent.cur_frame_set = FrameSet::IDLE;
	            framesComponent.animation_started = true;
                /*auto &sprite = entity->getComponent<SpriteComponent>();
                sprite.sprite.setTexture(framesComponent.base_frame);
				std::cout<< "time" << Timer::getTimer().getElapsedTime().asMicroseconds()<< '\n';
                std::cout << "aboba" << std::endl;*/
            }
        }
    }

    bool added() override {
        return true;
    }//TODO::find out what to return
};


#endif //GAME_FRAMESSYSTEM_H
