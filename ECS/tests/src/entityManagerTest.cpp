//
// Created by Андрей on 04.05.2023.
//

#include <gtest/gtest.h>
#include "../EntityManager.hpp"
#include "../Components/PositionComponent.h"
#include "../Components/VelocityComponent.h"



TEST(Entitymanager,selectEntitiy)
{
	EntityManager manager;
	Entity entity;
	entity.AddComponent<VelocityComponent>();
	manager.addEntity(&entity);
	auto vec = manager.selectEntites<VelocityComponent>();
	EXPECT_EQ(vec.size(),1);
	EXPECT_EQ(vec[0],&entity);
}

TEST(Entitymanager,addSystem)
{
	EntityManager manager;
	ISystem system;
	system.id = 1;
	manager.addSystem(&system);
	EXPECT_EQ(manager.getSystem(system.id),&system);
}


TEST(Entitymanager,selectEntities)
{
	EntityManager manager;
	Entity entityBoth;
	entityBoth.AddComponent<VelocityComponent>();
	entityBoth.AddComponent<PositionComponent>();
	manager.addEntity(&entityBoth);

	Entity entityVelocity;
	entityVelocity.AddComponent<VelocityComponent>();
	manager.addEntity(&entityVelocity);

	Entity entityPosition;
	entityPosition.AddComponent<PositionComponent>();
	manager.addEntity(&entityPosition);


	auto vec = manager.selectEntites<VelocityComponent,PositionComponent>();
	EXPECT_EQ(vec.size(),1);
	EXPECT_EQ(vec[0],&entityBoth);
}




