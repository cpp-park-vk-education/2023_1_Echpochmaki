//
// Created by Андрей on 04.05.2023.
//

#ifndef ECS_2023_1_ECHPOCHMAKI_ENTITYMANAGER_H_
#define ECS_2023_1_ECHPOCHMAKI_ENTITYMANAGER_H_

#include <set>

#include "ECS.h"
#include <SFML/Graphics.hpp>


struct ISystem // Fake system for compiling
{
    int id;
};


class Game; // Fake game for compiling


using namespace sf;

class EntityManager {
private:
    std::vector<Entity *> entities;
    std::set<ISystem *> systems;
public:
    void addEntity(Entity *entity) {
        entities.push_back(entity);
    }

    void setEntities(std::vector<Entity *> &&entities) {
        ; // Замена Всех энтити
    }

    bool addSystem(ISystem *system) // returns isSucceded
    {
        return systems.insert(system).second;
    }

    bool hasSystem(ISystem *system) // returns isSucceded
    {
        //return systems.contains(system);
        return true;
    }


    template<typename... TArgs>
    void selectEntites(std::vector<Entity *> &dest) {

        for (Entity *elem: entities)
            if (elem->HasComponents<TArgs...>())
                dest.push_back(elem);
    }

    Entity *getEntity(int keyID) {
        for (Entity *elem: entities)
            if (elem->id == keyID)
                return elem;
    }


    ISystem *getSystem(int keyID) {
        for (ISystem *system: systems)
            if (system->id == keyID)
                return system;
    }

    void update(Game *game) {
        //TODO::Make Implementation
    }


};


#endif //ECS_2023_1_ECHPOCHMAKI_ENTITYMANAGER_H_
