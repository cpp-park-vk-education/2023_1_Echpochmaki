//
// Created by Андрей on 04.05.2023.
//

#include <gtest/gtest.h>
#include "../ECS.h"
#include "../Components/PositionComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/VelocityComponent.h"



TEST(Component,positionComponent)
{
	Entity entity;
	entity.AddComponent<PositionComponent>(12,23);
	EXPECT_EQ(entity.GetComponent<PositionComponent>().position, Vector2<DistanceValueType>(12,23));
}

TEST(Component,velocityComponent)
{
	Entity entity;
	entity.AddComponent<VelocityComponent>(32,43);
	EXPECT_EQ(entity.GetComponent<PositionComponent>().position, Vector2<DistanceValueType>(32,43));
}

TEST(Component,spriteComponent)
{
	Entity entity;
	sf::Sprite spriteSrc;
	entity.AddComponent<SpriteComponent>(spriteSrc);
	EXPECT_EQ(spriteSrc.getTextureRect(),entity.GetComponent<SpriteComponent>().sprite.getTextureRect());
}

