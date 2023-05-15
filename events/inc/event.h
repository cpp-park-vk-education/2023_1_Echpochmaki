#pragma once

#include <SFML/Network.hpp>

struct Event
{
    void *some_data = nullptr;
    virtual ~Event() = default;
};

struct SyncSystemSyncEvent : Event
{
    sf::Packet *pack;
};

struct NetworkSyncFromHostEvent : Event
{
    sf::Packet *pack;
    sf::IpAddress sender_addr;
    sf::Uint16 sender_port;
};

struct NetworkSyncPlayerFromClientEvent : Event
{
    sf::Packet *pack;
    sf::IpAddress sender_addr;
    sf::Uint16 sender_port;
};

struct MapInfoReceivedEvent : Event
{
    sf::Packet *pack;
    sf::IpAddress sender_addr;
    sf::Uint16 sender_port;
    int seed;
};