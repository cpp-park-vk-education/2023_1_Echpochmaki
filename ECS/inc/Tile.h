#ifndef GAME_ENTITYTILEBASE_H
#define GAME_ENTITYTILEBASE_H

#include <vector>
#include <SFML/Network.hpp>

struct EntityTileBase {
    int objectId;

    EntityTileBase() : objectId(-1) {};
    constexpr explicit EntityTileBase(int id) : objectId(id) {};
};

static inline sf::Packet operator<<(sf::Packet& packet, const EntityTileBase& tile)
{
    return packet << sf::Int32(tile.objectId);
}

static inline sf::Packet operator>>(sf::Packet& packet, EntityTileBase& tile)
{
    sf::Int32 id;
    packet >> id;
    tile.objectId = id;
    return packet;
}


inline const int tileWidth = 60;
inline const int tileHeight = 60;

inline constexpr EntityTileBase fakeTile(-1);

inline constexpr EntityTileBase floorTile(0);
inline constexpr EntityTileBase wallTile(1);
inline constexpr EntityTileBase doorTile(2);

inline constexpr EntityTileBase enemyTile(3);
inline constexpr EntityTileBase playerTile(4);
inline constexpr EntityTileBase remotePlayerTile(5);

using tileMap = std::vector<std::vector<EntityTileBase>>;

#endif //GAME_ENTITYTILEBASE_H
