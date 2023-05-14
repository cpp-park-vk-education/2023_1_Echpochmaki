#ifndef ECS_HITBOXSYSTEM_H
#define ECS_HITBOXSYSTEM_H

#include "BaseSystem.h"
#include "../../inc/EntityManager.h"
#include "CollisionComponent.h"
#include "HealthComponent.h"
#include "AttackComponent.h"

const int HitBoxSystemID = 5;

class HitBoxSystem : public BaseSystem {
public:


    virtual void update(EntityManager *manager) {
        std::vector<Entity *> entities;
        manager->selectEntites<CollisionComponent>(entities);  //TODO::Might be costly

        for (auto it1 = entities.begin(); it1 != entities.end() - 1; it1++) {
            if ((*it1)->HasComponent<AttackComponent>()) {
                for (auto it2 = it1 + 1; it2 != entities.end(); it2++) {
                    if ((*it2)->HasComponent<HealthComponent>()) {
                        IntRect rect1 = (*it1)->getComponent<CollisionComponent>().collisionBox;
                        IntRect rect2 = (*it2)->getComponent<CollisionComponent>().collisionBox;
                        if (rect1.intersects(rect2))
                            (*it2)->getComponent<HealthComponent>().health -= (*it1)->getComponent<AttackComponent>().damage;
                    }
                }
            }
        }
    }

    virtual int getSystemID() override {
        return ID;
    }


    virtual bool added() {
        ID = HitBoxSystemID; //TODO::find out what to return
        return true;
    }

    ~HitBoxSystem() override = default;

private:
    static int ID;
};

#endif //ECS_HITBOXSYSTEM_H
