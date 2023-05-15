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
			auto& sprite = e->getComponent<SpriteComponent>().sprite;//TODO:: might be a wrong place to do this
			auto& position = e->getComponent<PositionComponent>().position;
			sprite.setPosition(position.x, position.y);
			if (e->HasComponent<CollisionComponent>())
			{

				auto& rect = e->getComponent<CollisionComponent>().collisionBox;

				sf::RectangleShape* rect_shape = new RectangleShape;
				rect_shape->setSize(Vector2f(rect.width, rect.height));
				rect_shape->move(position.x + rect.width / 2, position.y + rect.height / 2);
				window->draw(e->getComponent<SpriteComponent>().sprite);
				window->draw(*rect_shape);
			}
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
