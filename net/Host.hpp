#pragma once

#include "SFML/Network.hpp"
#include "IHost.hpp"

class Host : IHost {
    sf::UdpSocket socket;
    sf::IpAddress addr;
    sf::Uint16 port;

    virtual void handleClient(IClient* c) override;

    virtual void disconnectClient(int id) override;

    virtual bool send(sf::Packet& pack) override;
};
