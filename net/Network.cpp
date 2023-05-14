#include "Network.hpp"
#include "Host.hpp"
#include "Client.hpp"
#include "packets.hpp"
#include <iostream>


bool Network::isHost() const 
{
    return bool(currentHost);
}

bool Network::isClient() const 
{
    return bool(currentClient);
};

weak_ptr<IHost> Network::runHost() 
{
    // забиндить порт 

    currentHost = std::make_shared<Host>();

    if (currentHost->socket.bind(HOST_PORT) != sf::Socket::Done)
    {
        std::cerr << "[network] error to bind host socket";
        currentHost.reset();
    }
    else
    {
        currentHost->socket.setBlocking(false);
        currentHost->addr = "localhost";
        currentHost->port = currentHost->socket.getLocalPort();
    }

    return weak_ptr<IHost>(currentHost);
};

bool Network::connectToHost(const sf::IpAddress& addr, sf::Uint32 port) 
{
    // послать пакет о подключении, дождаться ответа

    currentClient = std::make_shared<Client>();

    if (currentClient->socket.bind(CLIENT_PORT) != sf::Socket::Done)
    {
        std::cerr << "[network] error to bind client socket";
        currentClient.reset();
        return false;
    }
    else
    {
        currentClient->socket.setBlocking(false);
        currentClient->addr = addr;
        currentClient->port = currentClient->socket.getLocalPort();
    }

    return currentClient->connectToHost(addr, port);
};

bool Network::closeHost() 
{
    // послать всем пакет о закрытии

    if (isHost())
        currentHost->disconnectAll();

    return false;
};

void Network::update()
{
    // проверить входящие пакеты и обработать их

    if (isClient())
    {
        sf::Packet pack;
        sf::IpAddress addr;
        sf::Uint16 port;
        currentClient->socket.receive(pack, addr, port);

        auto type = Packets::getPacketType(pack);

        if (type == Packets::SuccessConnection && currentClient->waiting_connect_answer)
        {
            // events fire connected to host
            currentClient->waiting_connect_answer = false;
        }
    }


    if (isHost())
    {
        sf::Packet pack;
        sf::IpAddress addr;
        sf::Uint16 port;
        currentHost->socket.receive(pack, addr, port);

        auto type = Packets::getPacketType(pack);

        

    }



};

bool Network::send(sf::Packet& packet) 
{
    // отправить хосту если клиент, клиентам если хост

    if (isHost())
        currentHost->send(packet);

    if (isClient())
        currentClient->send(packet);

    return true;
};   
