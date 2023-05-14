#ifndef ECS_BASESYSTEM_H
#define ECS_BASESYSTEM_H

#include "EntityManager.h"

class BaseSystem {
public:
    virtual int getSystemId();

    virtual void update(EntityManager *manager);

    virtual bool added();//TODO::find out what to return

    template<typename T>
    void setBefore();

    template<typename T>
    void setAfter();

    virtual ~BaseSystem() = default;

protected:
    static int system_id;
    int priority;
};

#endif //ECS_BASESYSTEM_H
