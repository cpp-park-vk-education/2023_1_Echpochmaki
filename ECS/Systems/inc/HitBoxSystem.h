#ifndef ECS_HITBOXSYSTEM_H
#define ECS_HITBOXSYSTEM_H

#include "BaseSystem.h"
#include "CollisionComponent.h"
#include "HealthComponent.h"
#include "AttackComponent.h"

const int MoveSystemID = 5;

class HitBoxSystem : BaseSystem
{
 public:
	virtual int getSystemId() override
	{
		return ID;
	}

	virtual void update(EntityManager* manager)
	{
		std::vector<Entity*> entities;
		manager->selectEntites<CollisionComponent>(entities);  //TODO::Might be costly

		for (auto it1 = entities.begin(); it1 != entities.end() - 1; it1++)
		{
			if ((*it1)->HasComponent<AttackComponent>())
			{
				for (auto it2 = it1 + 1; it2 != entities.end(); it2++)
				{
					if ((*it2)->HasComponent<HealthComponent>())
					{
						IntRect rect1 = (*it1)->getComponent<CollisionComponent>().collisionBox;
						IntRect rect2 = (*it2)->getComponent<CollisionComponent>().collisionBox;
						if (rect1.intersects(rect2))
							(*it2)->getComponent<HealthComponent>().health -= (*it1)->getComponent<AttackComponent>().damage;
					}
				}
			}
		}
	}

	virtual bool added()
	{
		ID = MoveSystemID; //TODO::find out what to return
		return true;
	}

	virtual ~HitBoxSystem();
 private:
	static int ID;
};

#endif //ECS_HITBOXSYSTEM_H
