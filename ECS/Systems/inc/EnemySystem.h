#ifndef ECS_ENEMYSYSTEM_H
#define ECS_ENEMYSYSTEM_H

#include "BaseSystem.h"
#include "PositionComponent.h"
#include "EnemyComponent.h"
#include "PlayerComponent.h"

#include "EntityManager.h"

#include "EnemyComponent.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include <cmath>





class EnemySystem : public BaseSystem {
public:


    void update(EntityManager* manager) override {
        //manager->
        std::vector<Entity*> enemies;
        std::vector<Entity*> players;
        manager->selectEntites<EnemyComponent>(enemies);
        manager->selectEntites<PlayerComponent>(players);

        Entity* player_selected = nullptr;

        for (auto enemy : enemies)
        {
            DistanceValueType min_distance = CalcDistance(enemy, players.front());

            for (auto player: players)
            {
                DistanceValueType cur_distance = CalcDistance(enemy, player);

                if (min_distance > cur_distance)
                {
                    min_distance = cur_distance;
                    player_selected = player;
                }
            }

            auto velocity_component = enemy->getComponent<VelocityComponent>();
            DistanceValueType len = velocity_component.velocity.x + velocity_component.velocity.y;
            Vector2<DistanceValueType> offset = CalcOffset(enemy, player_selected);
            Vector2<DistanceValueType> new_velocity = velocity_component.velocity / len;
            velocity_component.velocity = new_velocity;

            //Vector2<DistanceValueType> cur_vel = player_selected->getComponent<>()
        }

    }


    bool added() override
    {
        return true;
    }

    ~EnemySystem() override = default;

	virtual int getSystemID() override
	{
		return ID;
	}


 protected:
    // находит вектор, перемещающий e1 в e2
    static Vector2<DistanceValueType> CalcOffset(Entity* e1, Entity* e2) {
        auto pos1 = e1->getComponent<PositionComponent>();
        auto pos2 = e2->getComponent<PositionComponent>();

        return Vector2<DistanceValueType>{pos2.position.x - pos1.position.x, pos2.position.y - pos1.position.y};
    }

    static DistanceValueType CalcDistance(Entity* e1, Entity* e2) {
        auto pos1 = e1->getComponent<PositionComponent>();
        auto pos2 = e2->getComponent<PositionComponent>();

        auto distance = (DistanceValueType)sqrt(pow(pos1.position.x - pos2.position.x, 2) + pow(pos1.position.y - pos2.position.y, 2));

        return distance;
    }
 private:
	static int ID;

};

#endif //ECS_ENEMYSYSTEM_H
