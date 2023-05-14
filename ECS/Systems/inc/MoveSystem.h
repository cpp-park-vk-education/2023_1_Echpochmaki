#ifndef ECS_MOVESYSTEM_H
#define ECS_MOVESYSTEM_H

#include "BaseSystem.h"
#include "../../inc/EntityManager.h"
#include "../../inc/ECS.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "CollisionComponent.h"


const int MoveSystemID = 2;

class MoveSystem : public BaseSystem {
public:
    virtual int getSystemID() override {
        return MoveSystemID;
    }

    virtual void update(EntityManager *manager) override {
        std::vector<Entity *> entities;
        manager->selectEntites<PositionComponent>(entities);

        if (entities.size() == 1) {
            entities[0]->getComponent<PositionComponent>().position += entities[0]->getComponent<VelocityComponent>().velocity;
        }

        for (auto it1 = entities.begin(); it1 != entities.end() - 1; it1++) {
            if ((*it1)->HasComponent<VelocityComponent>()) {
                Vector2<DistanceValueType> oldPosition = (*it1)->getComponent<PositionComponent>().position;
                (*it1)->getComponent<PositionComponent>().position += (*it1)->getComponent<VelocityComponent>().velocity;
                if ((*it1)->HasComponent<CollisionComponent>()) {
                    for (auto it2 = it1 + 1; it2 != entities.end(); it2++) {
                        (*it1)->getComponent<CollisionComponent>().collisionBox.left = (*it1)->getComponent<PositionComponent>().position.x;
                        (*it1)->getComponent<CollisionComponent>().collisionBox.top = (*it1)->getComponent<PositionComponent>().position.y;
                        (*it2)->getComponent<CollisionComponent>().collisionBox.left = (*it2)->getComponent<PositionComponent>().position.x;
                        (*it2)->getComponent<CollisionComponent>().collisionBox.top = (*it2)->getComponent<PositionComponent>().position.y;
                        IntRect rect1 = (*it1)->getComponent<CollisionComponent>().collisionBox; //TODO::Might be costly
                        IntRect rect2 = (*it2)->getComponent<CollisionComponent>().collisionBox;
                        if (rect2.intersects(rect1)) {
                            (*it1)->getComponent<PositionComponent>().position = oldPosition;
                            (*it1)->getComponent<VelocityComponent>().velocity = {0, 0};
                            break;
                        }
                    }
                }
            }
        }

    }

    virtual bool added() override {

        return true; //TODO::find out what to return
    }

    ~MoveSystem() override = default;

private:
    static int ID;
};

#endif //ECS_MOVESYSTEM_H
