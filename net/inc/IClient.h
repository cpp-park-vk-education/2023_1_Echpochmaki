#pragma once

#include <memory>

#include "SFML/Network.hpp"
 


class IHost;

class IClient {
public:
    // std::unique_ptr<IHost> host;
    int id;
    sf::UdpSocket socket;
    sf::IpAddress addr;
    sf::Uint16 port;
    bool waiting_connect_answer = false;
    bool connected = false;
    bool map_received = false;

    virtual void disconnect() = 0;

    virtual bool connectToHost(const sf::IpAddress& addr, sf::Uint16 port) = 0;

    virtual bool send(sf::Packet& packet) = 0;
};

