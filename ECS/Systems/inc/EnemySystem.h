#ifndef ECS_ENEMYSYSTEM_H
#define ECS_ENEMYSYSTEM_H

#include "BaseSystem.h"


class EnemySystem : public BaseSystem {
public:
    virtual int getSystemId() override;

    virtual void update(EntityManager* manager) override;

    virtual bool added() override;

    virtual ~EnemySystem();
};

#endif //ECS_ENEMYSYSTEM_H
