#include "Host.h"
#include "Packets.h"
#include "IClient.h"
#include "Client.h"


void Host::handleClient(const sf::IpAddress& addr, sf::Uint16 host) 
{
    IClient *client = new Client;
    client->addr = addr;
    client->port = port;
    handleClient(client);
};

void Host::handleClient(IClient* c) 
{
    socket.send(Packets::successConnectionPack, c->addr, c->port);

    sf::Packet pack;
    // возможно переделать этот момент на ивенты или как то так, просто сейчас не знаю как получать данные о карте
    pack << Packets::MapGenerationInfo;
    // типа сид для карты
    pack << int(0);
    socket.send(pack, c->addr, c->port);

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
