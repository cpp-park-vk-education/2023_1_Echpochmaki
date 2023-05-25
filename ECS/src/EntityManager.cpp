//
// Created by Андрей on 04.05.2023.
//
#include "EntityManager.hpp"

void EntityManager::addEntity(Entity * entity)
{
	entities.push_back(entity);
}
bool  EntityManager::addSystem(ISystem* system) // returns isSucceded
{
	return systems.insert(system).second;
}


template<typename... TArgs>
void  EntityManager::selectEntites(std::vector<Entity*> &dest)
{
	//TODO::Implement this
}

Entity*  EntityManager::getEntity(int keyID)
{
	for (Entity* elem : entities)
		if (elem->id == keyID)
			return elem;
	
	return nullptr;
}


ISystem*  EntityManager::getSystem(int keyID)
{
	for (ISystem* system : systems)
		if (system->id == keyID)
			return system;
	
	return nullptr;
}

void  EntityManager::update(Game* game)
{
	//TODO::Make Implementation
}

void removeEntityDuplicates();