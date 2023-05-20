#ifndef GAME_ATTACKSYSTEM_H
#define GAME_ATTACKSYSTEM_H

#include "BaseSystem.h"
#include "../../inc/EntityManager.h"
#include "AttackComponent.h"
#include "HealthComponent.h"
#include "CollisionComponent.h"

const int AttackSystemId = 32521;

class AttackSystem : public BaseSystem {
public:
    AttackSystem() : ID(AttackSystemId) {}

    virtual void update(EntityManager *manager) {
        std::cout << "Here we go again" << std::endl;
        std::vector<Entity*> attackers;
        manager->selectEntites<AttackComponent>(attackers);
        std::vector<Entity*> goals;
        manager->selectEntites<HealthComponent>(goals);

        for (auto attacker: attackers)
        {
            for (auto goal : goals)
            {
                if (attacker != goal && goal->HasComponent<HealthComponent>())
                {
                    if (attacker->HasComponent<CollisionComponent>() && goal->HasComponent<CollisionComponent>())
                    {
                        auto rect = attacker->getComponent<CollisionComponent>().collisionBox;
                        std::cout << "Rect before: " << rect.height << rect.width << std::endl;

                        auto& attack_component = attacker->getComponent<AttackComponent>();
                        rect.height = attack_component.attackBox.height;
                        rect.width = attack_component.attackBox.width;

                        std::cout << "Rect after: " << rect.height << rect.width << std::endl;

                        if (goal->getComponent<CollisionComponent>().collisionBox.intersects(rect) &&
                            attacker->getComponent<AttackComponent>().attack_started)
                        {
                            goal->getComponent<HealthComponent>().health -= attacker->getComponent<AttackComponent>().damage;
							if (goal->getComponent<HealthComponent>().health <=0) {


                                goal->getComponent<FramesComponent>().dying = true;

                                if (attacker->HasComponent<PlayerComponent>()) {
                                    auto &playerComponent = attacker->getComponent<PlayerComponent>();
                                    playerComponent.kills += 1;
                                }
                            }
                        }
                    }

                }
            }
        }
    }

    virtual int getSystemID() override {
        return ID;
    }


    virtual bool added() {
        ID = AttackSystemId; //TODO::find out what to return
        return true;
    }

    ~AttackSystem() override = default;

private:
    int ID;
};

#endif //GAME_ATTACKSYSTEM_H
