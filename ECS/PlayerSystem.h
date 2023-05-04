#ifndef ECS_PLAYERSYSTEM_H
#define ECS_PLAYERSYSTEM_H

#include "BaseSystem.h"

class PlayerSystem : BaseSystem {
public:
    virtual void update(EntityManager* manager) override;

    virtual bool added() override;

    virtual ~PlayerSystem();
};


#endif //ECS_PLAYERSYSTEM_H
