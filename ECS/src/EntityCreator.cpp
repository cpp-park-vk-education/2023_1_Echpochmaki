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
#include "PlayerComponent.h"
#include "../../Game.h"
#include "../../assets/Assets.h"

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
        case floorTile.objectId: {
            Assets::loadTextureFromFile(floor_texture_path, *texture);
//            texture->loadFromFile(floor_texture_path);
            sprite.setTexture(*texture);
            entity->AddComponent<SpriteComponent>(sprite, floorTile.objectId);
        }
            break;
        case wallTile.objectId: {
            Assets::loadTextureFromFile(wall_texture_path, *texture);
//            texture->loadFromFile(wall_texture_path);
            sprite.setTexture(*texture);

            entity->AddComponent<SpriteComponent>(sprite, wallTile.objectId);
            entity->AddComponent<CollisionComponent>(IntRect(0, 0, DefaultCollideWidth, DefaultCollideHeight));
        }
            break;
        case doorTile.objectId: {
            Assets::loadTextureFromFile(door_texture_path, *texture);
//            texture->loadFromFile(door_texture_path);
            sprite.setTexture(*texture);

            entity->AddComponent<SpriteComponent>(sprite, doorTile.objectId);
        }
            break;
        case enemyTile.objectId: {
            entity->AddComponent<EnemyComponent>();
            entity->AddComponent<VelocityComponent>(1, 1);
            entity->AddComponent<MoveDirectionComponent>();
            entity->AddComponent<HealthComponent>(1);
            entity->AddComponent<AttackComponent>(1);
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


            std::vector<float> moving_frames_durations(moving_frames.size(), 1);
            std::vector<float> attack_frames_durations(attack_frames.size(), 1);
            std::vector<float> idling_frames_durations(idling_frames.size(), 2);
            std::vector<float> die_frames_durations(dying_frames.size(), 3);

            std::vector<std::vector<float>> all_animation_durations;
            all_animation_durations.push_back(moving_frames_durations);
            all_animation_durations.push_back(attack_frames_durations);
            all_animation_durations.push_back(idling_frames_durations);
            all_animation_durations.push_back(die_frames_durations);

            entity->AddComponent<FramesComponent>(all_frames, all_frames[0][0], all_animation_durations);

            sprite.setTexture(frames[0]);

            entity->AddComponent<SpriteComponent>(sprite, enemyTile.objectId);
            entity->AddComponent<CollisionComponent>(IntRect(0, 0, MovableCollideWidth, MovableCollideHeight),
                                                     Vector2<DistanceValueType>(MovableCollideWidth / 2,
                                                                                MovableCollideHeight / 2));
        }
            break;

        case playerTile.objectId: {
            entity->AddComponent<PositionComponent>(200, 200);
            entity->AddComponent<VelocityComponent>();
            entity->AddComponent<PlayerComponent>();
            entity->AddComponent<AttackComponent>(2);
            entity->AddComponent<MoveDirectionComponent>();
            //player.AddComponent<CollisionComponent>(IntRect(0, 0, 30, 40), Vector2<DistanceValueType>(30 / 2, 40 / 2));
            entity->AddComponent<SinkableComponent>(random());
            entity->AddComponent<HealthComponent>(100);

            //    player.AddComponent<AttackAnimationComponent>(attack_frames, frames[0]);
            //    player.AddComponent<AnimationMovingComponent>(moving_frames, frames[0]);

            auto frames_player = creator.GetFrames(9, 10, 14, 40, 0, 0);

            std::vector<sf::Texture> moving_frames_player{frames_player.begin() + 8, frames_player.begin() + 17};
            std::vector<sf::Texture> attack_frames_player{frames_player.begin() + 18, frames_player.begin() + 24};
            std::vector<sf::Texture> idling_frames_player{frames_player.begin() + 0, frames_player.begin() + 7};
            std::vector<sf::Texture> dying_frames_player{frames_player.begin() + 49, frames_player.begin() + 57};

            std::vector<std::vector<sf::Texture>> all_frames_player;
            all_frames_player.push_back(moving_frames_player);
            all_frames_player.push_back(attack_frames_player);
            all_frames_player.push_back(idling_frames_player);
            all_frames_player.push_back(dying_frames_player);


            std::vector<float> moving_frames_durations_player(moving_frames_player.size(), 1);
            std::vector<float> attack_frames_durations_player(attack_frames_player.size(), 1);
            std::vector<float> idling_frames_durations_player(idling_frames_player.size(), 2);
            std::vector<float> die_frames_durations_player(dying_frames_player.size(), 3);

            std::vector<std::vector<float>> all_animation_durations_player;
            all_animation_durations_player.push_back(moving_frames_durations_player);
            all_animation_durations_player.push_back(attack_frames_durations_player);
            all_animation_durations_player.push_back(idling_frames_durations_player);
            all_animation_durations_player.push_back(die_frames_durations_player);

            entity->AddComponent<FramesComponent>(all_frames_player, all_frames_player[0][0],
                                                  all_animation_durations_player);
            sprite.setTexture(frames_player[0]);

            entity->AddComponent<SpriteComponent>(sprite, playerTile.objectId);
            entity->AddComponent<CollisionComponent>(IntRect(0, 0, MovableCollideWidth, MovableCollideHeight),
                                                     Vector2<DistanceValueType>(MovableCollideWidth / 2,
                                                                                MovableCollideHeight / 2));
        }
            break;

        case remotePlayerTile.objectId:
        {
            entity->AddComponent<PositionComponent>(200, 200);
            entity->AddComponent<VelocityComponent>();
            entity->AddComponent<PlayerComponent>();
            entity->getComponent<PlayerComponent>().is_remote = true;
            entity->AddComponent<AttackComponent>(2);
            entity->AddComponent<MoveDirectionComponent>();
            //player.AddComponent<CollisionComponent>(IntRect(0, 0, 30, 40), Vector2<DistanceValueType>(30 / 2, 40 / 2));
            entity->AddComponent<SinkableComponent>(random());
            entity->AddComponent<HealthComponent>(100);

            //    player.AddComponent<AttackAnimationComponent>(attack_frames, frames[0]);
            //    player.AddComponent<AnimationMovingComponent>(moving_frames, frames[0]);

            auto frames_player = creator.GetFrames(9, 10, 14, 40, 0, 0);

            std::vector<sf::Texture> moving_frames_player{frames_player.begin() + 8, frames_player.begin() + 17};
            std::vector<sf::Texture> attack_frames_player{frames_player.begin() + 18, frames_player.begin() + 24};
            std::vector<sf::Texture> idling_frames_player{frames_player.begin() + 0, frames_player.begin() + 7};
            std::vector<sf::Texture> dying_frames_player{frames_player.begin() + 49, frames_player.begin() + 57};

            std::vector<std::vector<sf::Texture>> all_frames_player;
            all_frames_player.push_back(moving_frames_player);
            all_frames_player.push_back(attack_frames_player);
            all_frames_player.push_back(idling_frames_player);
            all_frames_player.push_back(dying_frames_player);


            std::vector<float> moving_frames_durations_player(moving_frames_player.size(), 1);
            std::vector<float> attack_frames_durations_player(attack_frames_player.size(), 1);
            std::vector<float> idling_frames_durations_player(idling_frames_player.size(), 2);
            std::vector<float> die_frames_durations_player(dying_frames_player.size(), 3);

            std::vector<std::vector<float>> all_animation_durations_player;
            all_animation_durations_player.push_back(moving_frames_durations_player);
            all_animation_durations_player.push_back(attack_frames_durations_player);
            all_animation_durations_player.push_back(idling_frames_durations_player);
            all_animation_durations_player.push_back(die_frames_durations_player);

            entity->AddComponent<FramesComponent>(all_frames_player, all_frames_player[0][0],
                                                  all_animation_durations_player);
            sprite.setTexture(frames_player[0]);

            entity->AddComponent<SpriteComponent>(sprite, playerTile.objectId);
            entity->AddComponent<CollisionComponent>(IntRect(0, 0, MovableCollideWidth, MovableCollideHeight),
                                                     Vector2<DistanceValueType>(MovableCollideWidth / 2,
                                                                                MovableCollideHeight / 2));
        }
            break;
        default:
            break;
    }

    return entity;
}

std::vector<Entity *> EntityCreator::createEntitiesByMap(const tileMap &tilemap) {
    std::cout << "[entitycreator] " << INFO << " createEntitiesByMap entered" << std::endl;

    std::vector<Entity *> entities;

    for (size_t i = 0; i < tilemap.size(); ++i) {
        for (size_t j = 0; j < tilemap[0].size(); ++j) {

            if (tilemap[i][j].objectId == enemyTile.objectId ||
                tilemap[i][j].objectId == playerTile.objectId /* ||
                tilemap[i][j].objectId == remotePlayerTile.objectId*/) {

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

Entity *EntityCreator::createPlayer(bool is_remote)
{
    auto entity = new Entity;
    std::string hero_king_texture_path = "../Graphics/textures/HeroKnight.png";

    FramesCreator creator(hero_king_texture_path);
    Sprite sprite;


    entity->AddComponent<PositionComponent>(200, 200);
    entity->AddComponent<VelocityComponent>();
    entity->AddComponent<PlayerComponent>();
    entity->getComponent<PlayerComponent>().is_remote = is_remote;
    entity->AddComponent<AttackComponent>(2);
    entity->AddComponent<MoveDirectionComponent>();
    //player.AddComponent<CollisionComponent>(IntRect(0, 0, 30, 40), Vector2<DistanceValueType>(30 / 2, 40 / 2));
    entity->AddComponent<SinkableComponent>(random());
    entity->AddComponent<HealthComponent>(100);

    //    player.AddComponent<AttackAnimationComponent>(attack_frames, frames[0]);
    //    player.AddComponent<AnimationMovingComponent>(moving_frames, frames[0]);

    auto frames_player = creator.GetFrames(9, 10, 14, 40, 0, 0);

    std::vector<sf::Texture> moving_frames_player{frames_player.begin() + 8, frames_player.begin() + 17};
    std::vector<sf::Texture> attack_frames_player{frames_player.begin() + 18, frames_player.begin() + 24};
    std::vector<sf::Texture> idling_frames_player{frames_player.begin() + 0, frames_player.begin() + 7};
    std::vector<sf::Texture> dying_frames_player{frames_player.begin() + 49, frames_player.begin() + 57};

    std::vector<std::vector<sf::Texture>> all_frames_player;
    all_frames_player.push_back(moving_frames_player);
    all_frames_player.push_back(attack_frames_player);
    all_frames_player.push_back(idling_frames_player);
    all_frames_player.push_back(dying_frames_player);


    std::vector<float> moving_frames_durations_player(moving_frames_player.size(), 1);
    std::vector<float> attack_frames_durations_player(attack_frames_player.size(), 1);
    std::vector<float> idling_frames_durations_player(idling_frames_player.size(), 2);
    std::vector<float> die_frames_durations_player(dying_frames_player.size(), 3);

    std::vector<std::vector<float>> all_animation_durations_player;
    all_animation_durations_player.push_back(moving_frames_durations_player);
    all_animation_durations_player.push_back(attack_frames_durations_player);
    all_animation_durations_player.push_back(idling_frames_durations_player);
    all_animation_durations_player.push_back(die_frames_durations_player);

    entity->AddComponent<FramesComponent>(all_frames_player, all_frames_player[0][0],
                                          all_animation_durations_player);
    sprite.setTexture(frames_player[0]);

    entity->AddComponent<SpriteComponent>(sprite, playerTile.objectId);
    entity->AddComponent<CollisionComponent>(IntRect(0, 0, MovableCollideWidth, MovableCollideHeight),
                                             Vector2<DistanceValueType>(MovableCollideWidth / 2,
                                                                        MovableCollideHeight / 2));

    return entity;
}


void EntityCreator::packTileMap(const tileMap &tilemap, sf::Packet& pack)
{
    pack << sf::Int32(tilemap.size()) << sf::Int32(tilemap[0].size());
    for (size_t i = 0; i < tilemap.size(); ++i) {
        for (size_t j = 0; j < tilemap[0].size(); ++j) {
            if (tilemap[i][j].objectId == playerTile.objectId)
                pack << remotePlayerTile;
            else
                pack << tilemap[i][j];
        }
    }
}

void EntityCreator::loadTileMap(sf::Packet& pack)
{
    Entity::nextId(true);
    std::cout << "[entitycreator] " << INFO << " loadTileMap enter Game::instance=" << Game::instance << std::endl;

    auto &manager = Game::instance->entityManager;
    manager->entities.clear();
    tileMap map;

    sf::Int32 map_width, map_height;
    pack >> map_width >> map_height;

    std::cout << "[entitycreator] " << INFO << " read map width=" << map_width << " height=" << map_height << std::endl;

    map.resize(map_width);
    for (auto &l : map)
        l.resize(map_height);

    for (size_t i = 0; i < map_width; ++i) {
        for (size_t j = 0; j < map_height; ++j) {
            pack >> map[i][j];
        }
    }

    std::cout << "[entitycreator] " << INFO << " map from packet loaded" << std::endl;
    std::cout.flush();

    auto entities = createEntitiesByMap(map);

    std::cout << "[entitycreator] " << INFO << " entities from map created" << std::endl;
    std::cout.flush();

    for (auto entity: entities) {
        manager->addEntity(entity);
    }

    std::cout << "[entitycreator] " << INFO << " all entities added" << std::endl;
    std::cout.flush();
}