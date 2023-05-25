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
	void addEntity(Entity * entity);

	bool addSystem(ISystem* system); // returns isSucceded



	template<typename... TArgs>
	void selectEntites(std::vector<Entity*> &dest);

	Entity* getEntity(int keyID);



	ISystem* getSystem(int keyID);


	void update(Game* game);

	void removeEntityDuplicates();



};


#endif //ECS_2023_1_ECHPOCHMAKI_ENTITYMANAGER_H_
