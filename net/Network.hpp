#pragma once

#include "SFML/Network.hpp"
#include "IHost.hpp"
#include "IClient.hpp"
#include <memory>

using std::weak_ptr;
using std::shared_ptr;

class Network {

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
};
