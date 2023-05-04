#ifndef ECS_SYNCSYSTEM_H
#define ECS_SYNCSYSTEM_H

#include "BaseSystem.h"

class SyncSystem : BaseSystem {
public:
    virtual void update(EntityManager* manager);

    virtual bool added();

    virtual ~SyncSystem();
};


#endif //ECS_SYNCSYSTEM_H
