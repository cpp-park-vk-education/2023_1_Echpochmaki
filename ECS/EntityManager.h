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


struct Game // Fake game for compiling
{

};



using namespace sf;

class EntityManager
{
 private:
	std::vector<Entity*> entities;
	std::set<ISystem*> systems;
 public:
	void addEntity(Entity * entity)
	{
		entities.push_back(entity);
	}
	bool addSystem(ISystem* system) // returns isSucceded
	{
		return systems.insert(system).second;
	}


	template<typename... TArgs>
	void selectEntites(std::vector<Entity*> &dest)
	{
		//TODO::Implement this
	}

	Entity* getEntity(int keyID)
	{
		for (Entity* elem : entities)
			if (elem->id == keyID)
				return elem;
	}


	ISystem* getSystem(int keyID)
	{
		for (ISystem* system : systems)
			if (system->id == keyID)
				return system;
	}

	void update(Game* game)
	{
		//TODO::Make Implementation
	}
	



};


#endif //ECS_2023_1_ECHPOCHMAKI_ENTITYMANAGER_H_
