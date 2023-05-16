#ifndef ECS_PLAYERSYSTEM_H
#define ECS_PLAYERSYSTEM_H

#include "BaseSystem.h"
#include "PlayerComponent.h"
#include "VelocityComponent.h"
#include "../../inc/EntityManager.h"
#include "AttackAnimationComponent.h"
#include "SpriteComponent.h"
#include "AnimationMovingComponent.h"
#include "AttackComponent.h"


const int PlayerSystemID = 234;

class PlayerSystem : public BaseSystem //TODO:: must be used before intersections or everything else
{
public:
    virtual int getSystemID() override {
        return PlayerSystemID;
    }

    virtual void update(EntityManager *manager) override {
        std::vector<Entity *> entities;
        manager->selectEntites<PlayerComponent>(entities);
        for (Entity *e: entities) {
            controlEntity(e);
        }
    }

    bool isHost() {
        return is_host;
    }


    virtual bool added() override {
        return true; //TODO::find out what to return
    }

    ~PlayerSystem() override = default;

protected:
    void controlEntity(Entity *entity) {
        if (entity->HasComponent<VelocityComponent>()) {
            int dir; //Handling the direction
            if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A)))) {
                dir = -1;
            } else if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D)))) {
                dir = 1;
            } else if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W)))) {
                dir = 3;
            } else if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S)))) {
                dir = 2;
            } else {
                dir = 0;
            }

//            auto& attack = entity->getComponent<AttackAnimationComponent>();
            auto &framesComponent = entity->getComponent<FramesComponent>();
            auto &attackComponent = entity->getComponent<AttackComponent>();
            if (Mouse::isButtonPressed(Mouse::Left)) {
                framesComponent.cur_frame_set = FrameSet::ATTACK;
                framesComponent.animation_started = true;
                attackComponent.attack_started = true;

                //std::cout << "left btn clicked" << std::endl;
            }
            else
            {
                attackComponent.attack_started = false;
            }

            Vector2<DistanceValueType> newVelocity = entity->getComponent<VelocityComponent>().velocity;
            DistanceValueType defaultSpeed = entity->getComponent<PlayerComponent>().speed;
            switch (dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
            {
                case 1:
                    newVelocity.x = defaultSpeed;
                    newVelocity.y = 0;
                    break;
                case -1:
                    newVelocity.x = -defaultSpeed;
                    newVelocity.y = 0;
                    break;
                case 2:
                    newVelocity.x = 0;
                    newVelocity.y = defaultSpeed;
                    break;
                case 3:
                    newVelocity.x = 0;
                    newVelocity.y = -defaultSpeed;
                    break;
                case 0:
                    newVelocity.x = 0;
                    newVelocity.y = 0;
                    break;

            }
            entity->getComponent<VelocityComponent>().velocity = newVelocity;
        }

    }

private:
    static int ID;
    bool is_host;
};

#endif //ECS_PLAYERSYSTEM_H
