#ifndef ECS_MOVESYSTEM_H
#define ECS_MOVESYSTEM_H

#include "BaseSystem.h"


class MoveSystem : public BaseSystem {
public:
    virtual void update(EntityManager* manager) override;

    virtual bool added() override;

    virtual ~MoveSystem();
};


#endif //ECS_MOVESYSTEM_H
