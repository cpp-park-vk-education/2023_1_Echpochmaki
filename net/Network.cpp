#include "Network.hpp"


bool Network::isHost() const 
{
    return false;
}

bool Network::isClient() const 
{
    return false;
};

weak_ptr<IHost> Network::runHost() 
{
    return weak_ptr<IHost>(shared_ptr<IHost>(nullptr));
};

bool Network::connectToHost(const sf::IpAddress& addr, sf::Uint32 port) 
{
    return false;
};

bool Network::closeHost() 
{
    return false;
};

void Network::update()
{

};

bool Network::send(sf::Packet& packet) 
{
    return false;
};   
