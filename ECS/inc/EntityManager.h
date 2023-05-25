//
// Created by Андрей on 04.05.2023.
//

#ifndef ECS_2023_1_ECHPOCHMAKI_ENTITYMANAGER_H_
#define ECS_2023_1_ECHPOCHMAKI_ENTITYMANAGER_H_

#include <set>

#include "ECS.h"
#include <SFML/Graphics.hpp>
#include "BaseSystem.h"
#include <set>


class Game; // Fake game for compiling


using namespace sf;


class EntityManager {
    static const constexpr auto BaseSystemPtrComparator = [](BaseSystem *a, BaseSystem *b) {
        return a->getSystemID() < b->getSystemID();
    };
public:
    std::vector<Entity*> entities;
    std::set<BaseSystem *, decltype(BaseSystemPtrComparator)> systems{BaseSystemPtrComparator};

public:
    ~EntityManager()
    {
//        for (auto e : entities)
//            delete e;
//        entities.clear();
//
//        for (auto s : systems)
//            delete s;
//        systems.clear();
    }

    void addEntity(Entity *entity) {
        entities.push_back(entity);
    }

    void setEntities(std::vector<Entity *> &&entities) {
        ; // Замена Всех энтити
    }

    bool addSystem(BaseSystem *system) // returns isSucceded
    {
        //  std::cout << "System size: " << systems.size() << std::endl;
        auto result = systems.insert(system);
        if (result.second)
            system->added();
        return result.second;
    }

//    auto addSystem2(BaseSystem *system) // returns isSucceded
//    {
////        std::cout << "System size: " << systems.size() << std::endl;
//        return systems.insert(system);
//    }


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
		return nullptr;
    }

    void update(Game *game) {
        for (auto s: systems) {
            s->update(this);
        }
        removeDuplicates();
        //TODO::Make Implementation
    }

    void deleteEntity(Entity* entity)
    {
//        auto it = std::find(entities.begin(), entities.end(), entity);
        std::remove(entities.begin(), entities.end(), entity);
        delete entity; //боже царя храни
    }

    bool deleteEntityById(int id)
    {
        for (auto it = entities.begin(); it != entities.end(); ++it)
        {
            if (id == (*it)->id)
            {
                delete *it;
                entities.erase(it);
                return true;
            }
        }

        return false;
    }

    void removeDuplicates()
    {
        std::set<Entity*> s( entities.begin(), entities.end() );
        entities.assign( s.begin(), s.end() );
    }
};


#endif //ECS_2023_1_ECHPOCHMAKI_ENTITYMANAGER_H_
