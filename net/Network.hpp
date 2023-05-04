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


    bool isHost() const {return false;};
    bool isClient() const {return false;};

    weak_ptr<IHost> runHost() {return weak_ptr<IHost>(shared_ptr<IHost>(nullptr));};

    bool connectToHost(const sf::IpAddress& addr, sf::Uint32 port) {return false;};

    bool closeHost() {return false;};

    void update(){}; 

    bool send(sf::Packet& packet) {return false;};   

};
