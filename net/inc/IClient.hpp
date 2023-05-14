#pragma once

#include <memory>

#include "SFML/Network.hpp"
 


class IHost;

class IClient {
public:
    std::unique_ptr<IHost> host;
    int id;

    virtual void disconnect() = 0;

    virtual bool send(sf::Packet& packet) = 0;
};

