#ifndef ECS_PLAYERSYSTEM_H
#define ECS_PLAYERSYSTEM_H

#include "BaseSystem.h"
#include "PlayerComponent.h"
#include "VelocityComponent.h"

const int PlayerSystemID = 234;

void controlEntity(Entity* entity)
{
	if (entity->HasComponent<VelocityComponent>())
	{
		int dir; //Handling the
		if ((Keyboard::isKeyPressed(Keyboard::Left) || (Keyboard::isKeyPressed(Keyboard::A))))
			dir = -1;
		else if ((Keyboard::isKeyPressed(Keyboard::Right) || (Keyboard::isKeyPressed(Keyboard::D))))
			dir = 1;
		else if ((Keyboard::isKeyPressed(Keyboard::Up) || (Keyboard::isKeyPressed(Keyboard::W))))
			dir = 3;
		else if ((Keyboard::isKeyPressed(Keyboard::Down) || (Keyboard::isKeyPressed(Keyboard::S))))
			dir = 2;

		Vector2<DistanceValueType> newVelocity = entity->getComponent<VelocityComponent>().velocity;
		DistanceValueType defaultSpeed = entity->getComponent<PlayerComponent>().speed;
		switch (dir)//реализуем поведение в зависимости от направления. (каждая цифра соответствует направлению)
		{
		case 1:
			newVelocity.x += defaultSpeed;
			newVelocity.y = 0;
			break;
		case -1:
			newVelocity.x += -defaultSpeed;
			newVelocity.y = 0;
			break;
		case 2:
			newVelocity.x = 0;
			newVelocity.y += defaultSpeed;
			break;
		case 3:
			newVelocity.x = 0;
			newVelocity.y += -defaultSpeed;
			break;
		}
		entity->getComponent<VelocityComponent>().velocity = newVelocity;
	}

}


class PlayerSystem : BaseSystem //TODO:: must be used before intersections or everything else
{
 public:
	virtual int getSystemId() override
	{
		return ID;
	}
	virtual void update(EntityManager* manager) override
	{
		std::vector<Entity*> entities;
		manager->selectEntites<PlayerComponent>(entities);
		for (Entity* e:entities)
		{
			controlEntity(e);
		}
	}

	virtual bool added() override
	{
		ID = PlayerSystemID;
		return true; //TODO::find out what to return
	}


	~PlayerSystem() override = default;
 private:
	static int ID;
};

#endif //ECS_PLAYERSYSTEM_H
