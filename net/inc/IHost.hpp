#pragma once

#include <vector>
#include <memory>

using std::vector;
using std::unique_ptr;

class IClient;

class IHost {

public:
    vector<unique_ptr<IClient>> connected;

    virtual void handleClient(IClient* c) = 0;

    virtual void disconnectClient(int id) = 0;

    virtual bool send(sf::Packet& pack) = 0;
};
