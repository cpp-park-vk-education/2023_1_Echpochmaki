#ifndef ECS_MOVESYSTEM_H
#define ECS_MOVESYSTEM_H

#include "BaseSystem.h"
#include "ECS.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"

class MoveSystem : public BaseSystem {
public:
    virtual int getSystemId() override;

    virtual void update(Ent;ityManager* manager) override {
        std::vector<Entity*> entyties;
        manager->selectEntites<PositionComponent, VelocityComponent>(entyties);

        for (e: entyties) {
            e->getComponent<PositionComponent>.position += e->getComponent<VelocityComponent>.velocity;
        }

    }

    virtual bool added() override;

    virtual ~MoveSystem();
};


#endif //ECS_MOVESYSTEM_H
