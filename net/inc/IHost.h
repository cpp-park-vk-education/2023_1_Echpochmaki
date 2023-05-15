#pragma once

#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;

class IClient;

class IHost {

public:
    vector<unique_ptr<IClient>> connected;
    sf::UdpSocket socket;
    sf::IpAddress addr;
    sf::Uint16 port;

    virtual ~IHost() = default;

    virtual void handleClient(IClient* c) = 0;

    virtual void disconnectClient(int id) = 0;
    virtual void disconnectClient(const sf::IpAddress& addr) = 0;


    virtual bool disconnectAll() = 0;

    virtual bool send(sf::Packet& pack) = 0;
};
