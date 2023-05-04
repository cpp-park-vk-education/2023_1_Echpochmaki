//
// Created by Андрей on 04.05.2023.
//
#include <gtest/gtest.h>
#include "../ECS.h"
#include "../EntityManager.hpp"
#include "../Components/PositionComponent.h"

using namespace std;




TEST(Entity,basicAdd)
{
	Entity entity;
	entity.AddComponent<PositionComponent>(32,32);
	EXPECT_EQ(entity.HasComponent<PositionComponent>(), true);
}

TEST(Entity,basicRemove)
{
	Entity entity;
	entity.AddComponent<PositionComponent>(32,32);
	entity.RemoveComponent<PositionComponent>();
	EXPECT_EQ(entity.HasComponent<PositionComponent>(), true);
}

TEST(Entity,)
{
	Entity entity;
	entity.AddComponent<PositionComponent>(32,32);
	entity.RemoveComponent<PositionComponent>();
	EXPECT_EQ(entity.HasComponent<PositionComponent>(), true);
}