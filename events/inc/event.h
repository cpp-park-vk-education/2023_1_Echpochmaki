#pragma once

#include <SFML/Network.hpp>

// ивент для нашей системы ивентов
struct OurEvent
{
    void *some_data = nullptr;
    virtual ~OurEvent() = default;
};

struct SyncSystemSyncEvent : OurEvent
{
    sf::Packet *pack;
};

struct NetworkSyncFromHostEvent : OurEvent
{
    sf::Packet *pack;
    sf::IpAddress sender_addr;
    sf::Uint16 sender_port;
};

struct NetworkSyncPlayerFromClientEvent : OurEvent
{
    sf::Packet *pack;
    sf::IpAddress sender_addr;
    sf::Uint16 sender_port;
};

struct MapInfoReceivedEvent : OurEvent
{
    sf::Packet *pack;
    sf::IpAddress sender_addr;
    sf::Uint16 sender_port;
    int seed;
};

struct NetworkDeleteEntitiesByIdsReceivedEvent : OurEvent
{
    sf::Packet *pack;
    sf::IpAddress sender_addr;
    sf::Uint16 sender_port;
    int seed;
};

struct NetworkDeleteEntitiesByIdsSendEvent : OurEvent
{
    sf::Packet *pack;
    int seed;
};