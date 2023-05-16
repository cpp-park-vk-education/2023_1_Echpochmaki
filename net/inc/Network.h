#pragma once

#include "SFML/Network.hpp"
#include "IHost.h"
#include "IClient.h"
#include <memory>

using std::weak_ptr;
using std::shared_ptr;

class Network {
public:
    static constexpr sf::Uint16 HOST_PORT = 5008;
    static constexpr sf::Uint16 CLIENT_PORT = 5007;


public:
    shared_ptr<IHost> currentHost;
    shared_ptr<IClient> currentClient;


    bool isHost() const;
    bool isClient() const;

    weak_ptr<IHost> runHost();

    bool connectToHost(const sf::IpAddress& addr, sf::Uint32 port);

    bool closeHost();

    void update(); 

    bool send(sf::Packet& packet);

private:
    
};
