#include "Host.hpp"
#include "packets.hpp"
#include "IClient.hpp"


void Host::handleClient(IClient* c) 
{
    connected.push_back(unique_ptr<IClient>(c));
};

void Host::disconnectClient(const sf::IpAddress& addr) 
{
    for (auto it = connected.begin(); it != connected.end(); it++)
    {
        if (it->operator->()->addr == addr)
        {
            sf::Packet pack;
            pack << Packets::DisconnectFromHost;
            socket.send(pack, it->operator->()->addr, it->operator->()->port);

            connected.erase(it);
            break;
        }
    }
};

void Host::disconnectClient(int id) 
{
    for (auto it = connected.begin(); it != connected.end(); it++)
    {
        if (it->operator->()->id == id)
        {
            sf::Packet pack;
            pack << Packets::DisconnectFromHost;
            socket.send(pack, it->operator->()->addr, it->operator->()->port);

            connected.erase(it);
            break;
        }
    }
};

bool Host::disconnectAll()
{
    sf::Packet pack;
    pack << sf::Int32(Packets::PacketType::DisconnectFromHost);
    for (auto &c : connected)
        socket.send(pack, c->addr, c->port);
    
    return true;
}


bool Host::send(sf::Packet& pack) 
{
    for (auto &c : connected)
        socket.send(pack, c->addr, c->port);
    
    return true;
};
