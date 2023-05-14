#ifndef ECS_MOVESYSTEM_H
#define ECS_MOVESYSTEM_H

#include "BaseSystem.h"
#include "ECS.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"
#include "CollisionComponent.h"

const int MoveSystemID = 4;

class MoveSystem : public BaseSystem
{
 public:
	virtual int getSystemId() override
	{
		return ID;
	}
	virtual void update(EntityManager* manager) override
	{
		std::vector<Entity*> entities;
		manager->selectEntites<PositionComponent, CollisionComponent>(entities);

		for (auto it1 = entities.begin(); it1 != entities.end() - 1; it1++)
		{
			if ((*it1)->HasComponent<VelocityComponent>())
			{
				Vector2<DistanceValueType> oldPosition = (*it1)->getComponent<PositionComponent>().position;
				(*it1)->getComponent<PositionComponent>().position += (*it1)->getComponent<VelocityComponent>().velocity;

				for (auto it2 = it1 + 1; it2 != entities.end(); it2++)
				{
					IntRect rect1 = (*it1)->getComponent<CollisionComponent>().collisionBox; //TODO::Might be costly
					IntRect rect2 = (*it2)->getComponent<CollisionComponent>().collisionBox;
					if (rect1.intersects(rect2))
					{
						(*it1)->getComponent<PositionComponent>().position = oldPosition;
						break;
					}
				}
			}
		}

	}

	virtual bool added() override
	{
		ID = MoveSystemID;
		return true; //TODO::find out what to return
	}

	virtual ~MoveSystem();
 private:
	static int ID;
};

#endif //ECS_MOVESYSTEM_H
