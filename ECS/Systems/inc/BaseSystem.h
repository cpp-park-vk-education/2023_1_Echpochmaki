#ifndef ECS_BASESYSTEM_H
#define ECS_BASESYSTEM_H

#include "ECS.h"
#include <SFML/Graphics.hpp>


class EntityManager;


class BaseSystem {
public:


    virtual int getSystemID() = 0;

    virtual void update(EntityManager* manager) = 0;

    virtual bool added() = 0;//TODO::find out what to return

   /* template <typename T>
    void setBefore();

    template <typename T>
    void setAfter();*/

    virtual ~BaseSystem() = default;



protected:
    static int system_id;
    int priority;


};

#endif //ECS_BASESYSTEM_H
