#include "../inc/EntityCreator.h"

#include "../utils/FramesCreator.h"

#include "SpriteComponent.h"
#include "CollisionComponent.h"
#include "PositionComponent.h"
#include "EnemyComponent.h"
#include "VelocityComponent.h"
#include "MoveDirectionComponent.h"
#include "FramesComponent.h"
#include "HealthComponent.h"
#include "AttackComponent.h"
#include "SinkableComponent.h"

const int DefaultCollideWidth = 60;
const int DefaultCollideHeight = 60;

const int MovableCollideWidth = 30;
const int MovableCollideHeight = 40;


Entity *EntityCreator::createEntity(const EntityTileBase &tile) {
    Entity *entity = new Entity;
    Sprite sprite;

    sf::Texture *texture = new sf::Texture;

    std::string floor_texture_path = "../Graphics/textures/floor.png";
    std::string wall_texture_path = "../Graphics/textures/wall.png";
    std::string door_texture_path = "../Graphics/textures/door.png";
    std::string hero_king_texture_path = "../Graphics/textures/HeroKnight.png";

    FramesCreator creator(hero_king_texture_path);

    switch (tile.objectId) {
        case floorTile.objectId:
            texture->loadFromFile(floor_texture_path);
            sprite.setTexture(*texture);
            entity->AddComponent<SpriteComponent>(sprite, floorTile.objectId);
            break;
        case wallTile.objectId:
            texture->loadFromFile(wall_texture_path);
            sprite.setTexture(*texture);

            entity->AddComponent<SpriteComponent>(sprite, wallTile.objectId);
            entity->AddComponent<CollisionComponent>(IntRect(0, 0, DefaultCollideWidth, DefaultCollideHeight));
            break;
        case doorTile.objectId:
            texture->loadFromFile(door_texture_path);
            sprite.setTexture(*texture);

            entity->AddComponent<SpriteComponent>(sprite, doorTile.objectId);
            break;
        case enemyTile.objectId:
            entity->AddComponent<EnemyComponent>();
            entity->AddComponent<VelocityComponent>(1, 1);
            entity->AddComponent<MoveDirectionComponent>();
            entity->AddComponent<HealthComponent>(1);
            entity->AddComponent<SinkableComponent>(random()); // подумать как сделать уникальный


                auto frames = creator.GetFrames(9, 10, 14, 40, 0, 0);

            std::vector<sf::Texture> moving_frames{frames.begin() + 8, frames.begin() + 17};
            std::vector<sf::Texture> attack_frames{frames.begin() + 18, frames.begin() + 24};
            std::vector<sf::Texture> idling_frames{frames.begin() + 0, frames.begin() + 7};
            std::vector<sf::Texture> dying_frames{frames.begin() + 49, frames.begin() + 57};

            std::vector<std::vector<sf::Texture>> all_frames;
            all_frames.push_back(moving_frames);
            all_frames.push_back(attack_frames);
            all_frames.push_back(idling_frames);
            all_frames.push_back(dying_frames);

            entity->AddComponent<FramesComponent>(all_frames, all_frames[0][0]);
            sprite.setTexture(frames[0]);

            entity->AddComponent<SpriteComponent>(sprite, enemyTile.objectId);
            entity->AddComponent<CollisionComponent>(IntRect(0, 0, MovableCollideWidth, MovableCollideHeight),Vector2<DistanceValueType>(MovableCollideWidth / 2, MovableCollideHeight / 2));
            break;
    }

    return entity;
}

std::vector<Entity *> EntityCreator::createEntitiesByMap(const tileMap &tilemap) {
    std::vector<Entity *> entities;

    for (size_t i = 0; i < tilemap.size(); ++i) {
        for (size_t j = 0; j < tilemap[0].size(); ++j) {

            if (tilemap[i][j].objectId == enemyTile.objectId) {
                Entity *entity = createEntity(floorTile);
                entity->AddComponent<PositionComponent>(j * tileWidth, i * tileHeight);
                entities.push_back(entity);
            }

            Entity *entity = createEntity(tilemap[i][j]);
            entity->AddComponent<PositionComponent>(j * tileWidth, i * tileHeight);
            entities.push_back(entity);
        }
    }

    return entities;
}