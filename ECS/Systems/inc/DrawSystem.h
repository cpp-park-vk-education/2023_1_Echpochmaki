//
// Created by Андрей on 14.05.2023.
//

#ifndef GAME_2023_1_ECHPOCHMAKI_ECS_SYSTEMS_INC_DRAWSYSTEM_H_
#define GAME_2023_1_ECHPOCHMAKI_ECS_SYSTEMS_INC_DRAWSYSTEM_H_

const int DrawSystemID = 2321;

#include "BaseSystem.h"
#include "SpriteComponent.h"
#include "CollisionComponent.h"

class DrawSystem : public BaseSystem
{
 public:

	virtual void update(EntityManager* manager)
	{
		std::vector<Entity*> entities;
		manager->selectEntites<SpriteComponent>(entities);

		for (Entity* e : entities)
		{
			e->getComponent<SpriteComponent>().sprite.setPosition(e->getComponent<PositionComponent>().position); //TODO:: might be a wrong place to do this
			window->draw(e->getComponent<SpriteComponent>().sprite);


		}
	}

	virtual bool added()
	{
		return true;
	}

	void setRenderWindow(RenderWindow* windowSrc)
	{
		window = windowSrc;
	}

	virtual int getSystemID() override
	{
		return DrawSystemID;
	}

	~DrawSystem() override = default;

 private:
	static int ID;
	RenderWindow* window;
};

#endif //GAME_2023_1_ECHPOCHMAKI_ECS_SYSTEMS_INC_DRAWSYSTEM_H_
