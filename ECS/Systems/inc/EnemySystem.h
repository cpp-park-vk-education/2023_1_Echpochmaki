#ifndef ECS_ENEMYSYSTEM_H
#define ECS_ENEMYSYSTEM_H

#include "BaseSystem.h"
#include "PositionComponent.h"
#include "EnemyComponent.h"
#include "PlayerComponent.h"

#include "../../inc/EntityManager.h"

#include "EnemyComponent.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include <cmath>
#include "SpriteComponent.h"
#include "AttackAnimationComponent.h"
#include "CollisionComponent.h"

const int EnemyId = 3456;


class EnemySystem : public BaseSystem {
public:


    void update(EntityManager *manager) override {
        //manager->
        std::vector<Entity *> enemies;
        std::vector<Entity *> players;
        manager->selectEntites<EnemyComponent>(enemies);
        manager->selectEntites<PlayerComponent>(players);

        Entity *player_selected = nullptr;

        for (auto enemy: enemies) {
            DistanceValueType min_distance = CalcDistance(enemy, players.front());
            bool collided = false;

            const auto& enemy_rect = enemy->getComponent<CollisionComponent>().collisionBox;
            for (const auto& player: players)
            {
                if (player->getComponent<CollisionComponent>().collisionBox.intersects(enemy_rect))
                {
                    std::cout << "collided wtf" << std::endl;
                    collided = true;
                }

                DistanceValueType cur_distance = CalcDistance(enemy, player);

                if (min_distance >= cur_distance)
                {
                    min_distance = cur_distance;
                    player_selected = player;
                }
            }

            //auto& attack = enemy->getComponent<AttackAnimationComponent>();
            if (enemy->HasComponent<FramesComponent>())
            {
                auto& framesComponent = enemy->getComponent<FramesComponent>();
                if (collided)
                {
                    framesComponent.animation_started = true;
                    framesComponent.cur_frame_set = FrameSet::ATTACK;
                }

//                if (!collided)
//                {
//                    framesComponent.animation_started = false;
//                }
            }

            auto& velocity_component = enemy->getComponent<VelocityComponent>();
//            std::cout << "default velocity: " << velocity_component.default_velocity.x << velocity_component.default_velocity.y << std::endl;
            DistanceValueType len = sqrt(pow(velocity_component.default_velocity.x, 2) + pow(velocity_component.default_velocity.y, 2));
            Vector2<DistanceValueType> offset = CalcOffset(enemy, player_selected);
            Vector2<DistanceValueType> velocity_to_set;

            if (len != 0)
            {
                DistanceValueType offset_len = sqrt(pow(offset.x, 2) + pow(offset.y, 2));
                Vector2<DistanceValueType> new_velocity = offset / offset_len * len;
                velocity_to_set = new_velocity;
            }
            else
            {
                DistanceValueType offset_len = sqrt(pow(offset.x, 2) + pow(offset.y, 2));
                //Vector2<DistanceValueType> new_velocity = offset / offset_len; // придумать как обрабатывать ситуацию клгда лен == 0,
                // пока вектор просто нормируется
                velocity_to_set = {0, 0};
            }
//            velocity_component.velocity = new_velocity;
                velocity_component.velocity.x = velocity_to_set.x;
                velocity_component.velocity.y = velocity_to_set.y;
        }

    }


    bool added() override {
        return true;
    }

    ~EnemySystem() override = default;

    virtual int getSystemID() override {
        return EnemyId;
    }


protected:
    // находит вектор, перемещающий e1 в e2
    static Vector2<DistanceValueType> CalcOffset(Entity* e1, Entity* e2) {

        if (!e1 || !e2)
        {
            throw std::runtime_error("Entity nullptr");
        }

        auto pos1 = e1->getComponent<PositionComponent>();
        auto pos2 = e2->getComponent<PositionComponent>();

        return Vector2<DistanceValueType>{pos2.position.x - pos1.position.x, pos2.position.y - pos1.position.y};
    }

    static DistanceValueType CalcDistance(Entity *e1, Entity *e2) {
        auto pos1 = e1->getComponent<PositionComponent>();
        auto pos2 = e2->getComponent<PositionComponent>();

        auto distance = (DistanceValueType) sqrt(
                pow(pos1.position.x - pos2.position.x, 2) + pow(pos1.position.y - pos2.position.y, 2));

        return distance;
    }
// private:
//	static int ID;

};

#endif //ECS_ENEMYSYSTEM_H
