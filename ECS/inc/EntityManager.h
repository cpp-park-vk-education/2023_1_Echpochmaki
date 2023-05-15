//
// Created by Андрей on 04.05.2023.
//

#ifndef ECS_2023_1_ECHPOCHMAKI_ENTITYMANAGER_H_
#define ECS_2023_1_ECHPOCHMAKI_ENTITYMANAGER_H_

#include <set>

#include "ECS.h"
#include <SFML/Graphics.hpp>
#include "BaseSystem.h"


class Game; // Fake game for compiling


using namespace sf;




class EntityManager {
    static const constexpr auto BaseSystemPtrComparator = [](BaseSystem *a, BaseSystem *b)
    {
        return a->getSystemID() < b->getSystemID();
    };
public:
    std::vector<Entity *> entities;
    std::set<BaseSystem *, decltype(BaseSystemPtrComparator)> systems{BaseSystemPtrComparator};

public:
    void addEntity(Entity *entity) {
        entities.push_back(entity);
    }

    void setEntities(std::vector<Entity *> &&entities) {
        ; // Замена Всех энтити
    }

    bool addSystem(BaseSystem *system) // returns isSucceded
    {
        std::cout << "System size: " << systems.size() << std::endl;
        return systems.insert(system).second;
    }

    auto addSystem2(BaseSystem *system) // returns isSucceded
    {
//        std::cout << "System size: " << systems.size() << std::endl;
        return systems.insert(system);
    }



    bool hasSystem(BaseSystem *system) // returns isSucceded
    {
        //return systems.contains(system);
        return false;
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


    BaseSystem *getSystem(int keyID) {
        for (BaseSystem *system: systems)
            if (system->getSystemID() == keyID)
                return system;
    }

    void update(Game *game) {
        for (auto s: systems) {
            s->update(this);
        }
        //TODO::Make Implementation
    }


};


#endif //ECS_2023_1_ECHPOCHMAKI_ENTITYMANAGER_H_
