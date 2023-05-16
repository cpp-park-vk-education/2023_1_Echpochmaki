#include <gtest/gtest.h>
#include <vector>

#include "AttackComponent.h"
#include "CollisionComponent.h"
#include "HealthComponent.h"
#include "PositionComponent.h"
#include "VelocityComponent.h"

#include "../../inc/MoveSystem.h"
#include "HitBox.h"

#include "EntityManager.h"

TEST(MoveSystemTest, BasicCaseX) {
    PositionComponent position(10, 10);
    VelocityComponent velocity(3, 3);
    Entity* entity = new Entity(position, velocity);
    std::vector<Entity*> entities;
    entities.push_back(entity);
    EntityManager.setEntities(std::move(entities));

    MoveSystem move_system;
    move_system.update(EntityManager);

    EXPECT_EQ(position.x, 13);
}

TEST(MoveSystemTest, BasicCaseY) {
    PositionComponent position(10, 10);
    VelocityComponent velocity(3, 3);
    Entity* entity = new Entity(position, velocity);
    std::vector<Entity*> entities;
    entities.push_back(entity);
    EntityManager.setEntities(std::move(entities));

    MoveSystem move_system;
    move_system.update(EntityManager);

    EXPECT_EQ(position.y, 13);
}

TEST(MoveSystemTest, BasicCaseFloatX) {
    PositionComponent position(10, 10);
    VelocityComponent velocity(3.5, 3.5);
    Entity* entity = new Entity(position, velocity);
    std::vector<Entity*> entities;
    entities.push_back(entity);
    EntityManager.setEntities(std::move(entities));

    MoveSystem move_system;
    move_system.update(EntityManager);

    EXPECT_EQ(position.x, 13.5);
}

TEST(MoveSystemTest, BasicCaseFloatY) {
    PositionComponent position(10, 10);
    VelocityComponent velocity(3.5, 3.5);
    Entity* entity = new Entity(position, velocity);
    std::vector<Entity*> entities;
    entities.push_back(entity);
    EntityManager.setEntities(std::move(entities));

    MoveSystem move_system;
    move_system.update(EntityManager);

    EXPECT_EQ(position.y, 13.5);
}

TEST(MoveSystemTest, NegativeVelocityIntX) {
    PositionComponent position(10, 10);
    VelocityComponent velocity(-1, -1);
    Entity* entity = new Entity(position, velocity);
    std::vector<Entity*> entities;
    entities.push_back(entity);
    EntityManager.setEntities(std::move(entities));

    MoveSystem move_system;
    move_system.update(EntityManager);

    EXPECT_EQ(position.x, 9);
}

TEST(MoveSystemTest, NegativeVelocityIntY) {
    PositionComponent position(10, 10);
    VelocityComponent velocity(-1, -1);
    Entity* entity = new Entity(position, velocity);
    std::vector<Entity*> entities;
    entities.push_back(entity);
    EntityManager.setEntities(std::move(entities));

    MoveSystem move_system;
    move_system.update(EntityManager);

    EXPECT_EQ(position.y, 9);
}

TEST(MoveSystemTest, NegativeVelocityFloatX) {
    PositionComponent position(10, 10);
    VelocityComponent velocity(-1.5, -1.5);
    Entity* entity = new Entity(position, velocity);
    std::vector<Entity*> entities;
    entities.push_back(entity);
    EntityManager.setEntities(std::move(entities));

    MoveSystem move_system;
    move_system.update(EntityManager);

    EXPECT_EQ(position.x, 8.5);
}

TEST(MoveSystemTest, NegativeVelocityFloatY) {
    PositionComponent position(10, 10);
    VelocityComponent velocity(-1.5, -1.5);
    Entity* entity = new Entity(position, velocity);
    std::vector<Entity*> entities;
    entities.push_back(entity);
    EntityManager.setEntities(std::move(entities));

    MoveSystem move_system;
    move_system.update(EntityManager);

    EXPECT_EQ(position.y, 8.5);
}

TEST(MoveSystemTest, TwoEntityIntX) {
    PositionComponent position1(10, 10);
    VelocityComponent velocity1(3.5, 3.5);
    PositionComponent position2(3, 3);
    VelocityComponent velocity2(1, 1);
    Entity* entity = new Entity(position, velocity);
    std::vector<Entity*> entities;
    entities.push_back(entity);
    EntityManager.setEntities(std::move(entities));

    MoveSystem move_system;
    move_system.update(EntityManager);

    EXPECT_EQ(position1.x, 13.5);
}

TEST(MoveSystemTest, TwoEntityIntY) {
    PositionComponent position1(10, 10);
    VelocityComponent velocity1(3.5, 3.5);
    PositionComponent position2(3, 3);
    VelocityComponent velocity2(1, 1);
    Entity* entity = new Entity(position, velocity);
    std::vector<Entity*> entities;
    entities.push_back(entity);
    EntityManager.setEntities(std::move(entities));

    MoveSystem move_system;
    move_system.update(EntityManager);

    EXPECT_EQ(position1.y, 13.5);
}

TEST(MoveSystemTest, TwoEntitySecondIntX) {
    PositionComponent position1(10, 10);
    VelocityComponent velocity1(3.5, 3.5);
    PositionComponent position2(3, 3);
    VelocityComponent velocity2(1, 1);
    Entity* entity = new Entity(position, velocity);
    std::vector<Entity*> entities;
    entities.push_back(entity);
    EntityManager.setEntities(std::move(entities));

    MoveSystem move_system;
    move_system.update(EntityManager);

    EXPECT_EQ(position2.x, 4);
}

TEST(MoveSystemTest, TwoEntitySecondIntY) {
    PositionComponent position1(10, 10);
    VelocityComponent velocity1(3.5, 3.5);
    PositionComponent position2(3, 3);
    VelocityComponent velocity2(1, 1);
    Entity* entity = new Entity(position, velocity);
    std::vector<Entity*> entities;
    entities.push_back(entity);
    EntityManager.setEntities(std::move(entities));

    MoveSystem move_system;
    move_system.update(EntityManager);

    EXPECT_EQ(position2.y, 4);
}

TEST(MoveSystemTest, TwoEntityNegativeVelocityX) {
    PositionComponent position1(10, 10);
    VelocityComponent velocity1(-3.5, -3.5);
    PositionComponent position2(3, 3);
    VelocityComponent velocity2(-1, -1);
    Entity* entity = new Entity(position, velocity);
    std::vector<Entity*> entities;
    entities.push_back(entity);
    EntityManager.setEntities(std::move(entities));

    MoveSystem move_system;
    move_system.update(EntityManager);

    EXPECT_EQ(position1.x, 6.5);
}

TEST(MoveSystemTest, TwoEntityNegativeVelocityY) {
    PositionComponent position1(10, 10);
    VelocityComponent velocity1(-3.5, -3.5);
    PositionComponent position2(3, 3);
    VelocityComponent velocity2(-1, -1);
    Entity* entity = new Entity(position, velocity);
    std::vector<Entity*> entities;
    entities.push_back(entity);
    EntityManager.setEntities(std::move(entities));

    MoveSystem move_system;
    move_system.update(EntityManager);

    EXPECT_EQ(position1.y, 6.5);
}

TEST(MoveSystemTest, TwoEntityNegativeVelocitySecondX) {
    PositionComponent position1(10, 10);
    VelocityComponent velocity1(-3.5, -3.5);
    PositionComponent position2(3, 3);
    VelocityComponent velocity2(-1, -1);
    Entity* entity = new Entity(position, velocity);
    std::vector<Entity*> entities;
    entities.push_back(entity);
    EntityManager.setEntities(std::move(entities));

    MoveSystem move_system;
    move_system.update(EntityManager);

    EXPECT_EQ(position2.x, 2);
}

TEST(MoveSystemTest, TwoEntityNegativeVelocitySecondY) {
    PositionComponent position1(10, 10);
    VelocityComponent velocity1(-3.5, -3.5);
    PositionComponent position2(3, 3);
    VelocityComponent velocity2(-1, -1);
    Entity* entity = new Entity(position, velocity);
    std::vector<Entity*> entities;
    entities.push_back(entity);
    EntityManager.setEntities(std::move(entities));

    MoveSystem move_system;
    move_system.update(EntityManager);

    EXPECT_EQ(position2.y, 2);
}
