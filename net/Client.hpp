#pragma once

#include "IClient.hpp"

class Client : public IClient {
    virtual bool connectToHost(const sf::IpAddress& addr, sf::Uint16 port) override;

    virtual void disconnect() override;

    virtual bool send(sf::Packet& packet) override;
};
