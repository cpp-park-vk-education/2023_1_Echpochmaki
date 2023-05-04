//
// Created by Андрей on 04.05.2023.
//
#include <gtest/gtest.h>
#include "../ECS.h"
#include "../Components/PositionComponent.h"

using namespace std;




TEST(Entity,basicAdd)
{
	Entity entity;
	entity.AddComponent<PositionComponent>(32,32);
	EXPECT_EQ(entity.HasComponent<PositionComponent>(), true);
}


TEST(Entity,basicAddDefaultConstruct)
{
	Entity entity;
	entity.AddComponent<PositionComponent>();
	EXPECT_EQ(entity.HasComponent<PositionComponent>(), true);
}


TEST(Entity,basicRemove)
{
	Entity entity;
	entity.AddComponent<PositionComponent>(32,32);
	entity.RemoveComponent<PositionComponent>();
	EXPECT_EQ(entity.HasComponent<PositionComponent>(), true);
}
TEST(Entity,failedRemove)
{
	Entity entity;
	EXPECT_EQ(entity.RemoveComponent<PositionComponent>(), false);
}




TEST(Entity,getComponentFailed)
{
	Entity entity;
	EXPECT_EQ(entity.HasComponent<PositionComponent>(), false);
}


TEST(Entity,doubleAdd)
{
	Entity entity;
	Entity entity2;
	auto component1 = entity.AddComponent<PositionComponent>(12,32);
	auto component2 = entity.AddComponent<PositionComponent>(43,12);
	EXPECT_EQ(&component2, &entity.GetComponent<PositionComponent>());
}


