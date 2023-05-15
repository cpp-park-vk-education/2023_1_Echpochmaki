#ifndef GAME_REMOVEENTITYSYSTEM_H
#define GAME_REMOVEENTITYSYSTEM_H

#include "BaseSystem.h"
#include "../../inc/EntityManager.h"
#include "HealthComponent.h"

const int RemoveSystemId = 32342521;

class RemoveSystem : public BaseSystem {
public:
    RemoveSystem() : ID(RemoveSystemId) {}

    virtual void update(EntityManager *manager)
    {
        std::cout << "Die die die my darling" << std::endl;
        std::vector<Entity*> entities;
        manager->selectEntites<HealthComponent>(entities);

        for (auto entity: entities)
        {
            auto& healthComponent = entity->getComponent<HealthComponent>();

            if (healthComponent.health <= 0)
            {
                manager->deleteEntity(entity);
            }

        }

    }

    virtual int getSystemID() override {
        return ID;
    }


    virtual bool added() {
        ID = RemoveSystemId; //TODO::find out what to return
        return true;
    }

    ~RemoveSystem() override = default;

private:
    int ID;
};

#endif //GAME_REMOVEENTITYSYSTEM_H
