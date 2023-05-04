#ifndef ECS_HITBOXSYSTEM_H
#define ECS_HITBOXSYSTEM_H

#include "BaseSystem.h"

class HitBoxSystem : BaseSystem {
public:
    virtual int getSystemId() override;

    virtual void update(EntityManager* entity);

    virtual bool added();

    virtual ~HitBoxSystem();
};

#endif //ECS_HITBOXSYSTEM_H
