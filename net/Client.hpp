#pragma once

#include "IClient.hpp"

class Client : IClient {
    sf::UdpSocket socket;
    sf::IpAddress addr;
    sf::Uint16 port;

    virtual void disconnect() override {};

    virtual bool send(sf::Packet& packet) override {return false;};
};
