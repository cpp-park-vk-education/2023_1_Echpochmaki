#pragma once

#include "SFML/Network.hpp"
#include "IHost.h"

struct Host : public IHost {

    // virtual sf::UdpSocket getSocket() = 0;

    virtual void handleClient(IClient* c) override;

    virtual void disconnectClient(int id) override;
    virtual void disconnectClient(const sf::IpAddress& addr) override;

    virtual bool disconnectAll() override;

    virtual bool send(sf::Packet& pack) override;
};
