#include "Network.h"
#include "Host.h"
#include "Client.h"
#include "Packets.h"
#include "events/inc/events.h"
#include <iostream>


bool Network::isHost() const 
{
    return bool(currentHost);
}

bool Network::isClient() const 
{
    return bool(currentClient);
};

Network::~Network()
{
    closeHost();
    closeClient();
};


Network::Network()
{
    Events::on(Events::EventType::SyncSystemClientToHostSendSync, [this](Event *event) 
    {
        SyncSystemSyncEvent *e = dynamic_cast<SyncSystemSyncEvent*>(event);
        if (isClient())
        {
            currentClient->send(*e->pack);
        }
    });

    Events::on(Events::EventType::SyncSystemHostToClientSendSync, [this](Event *event) 
    {
        SyncSystemSyncEvent *e = dynamic_cast<SyncSystemSyncEvent*>(event);
        if (isHost())
        {
            currentHost->send(*e->pack);
        }
    });
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

void Network::closeClient()
{
    if (isClient())
    {

        currentClient->disconnect();
        currentClient.reset();
    }
}


void Network::closeHost() 
{
    // послать всем пакет о закрытии

    if (isHost())
    {
        currentHost->disconnectAll();
        currentHost.reset();
    }

};

void Network::updateClient()
{
    sf::Packet pack;
    sf::IpAddress addr;
    sf::Uint16 port;
    currentClient->socket.receive(pack, addr, port);

    Packets::PacketType type = Packets::getPacketType(pack);

    if (type == Packets::SuccessConnection && currentClient->waiting_connect_answer)
    {
        // events fire connected to host
        currentClient->waiting_connect_answer = false;
        currentClient->connected = true;
    }

    if (type == Packets::MapGenerationInfo && currentClient->connected)
    {
        currentClient->map_received = true;
        MapInfoReceivedEvent event;
        event.pack = &pack;
        event.sender_addr = addr;
        event.sender_port = port;
        Events::fire(Events::EventType::MapInfoFromNetReceived, &event);
    }

    if (type == Packets::SyncAllEntitiesFromHost && currentClient->connected && currentClient->map_received)
    {
        NetworkSyncFromHostEvent event;
        event.pack = &pack;
        event.sender_addr = addr;
        event.sender_port = port;
        Events::fire(Events::EventType::NetworkSyncAllFromHostRecieved, &event);
    }

    if (type == Packets::DisconnectFromHost && currentClient->connected)
    {
        closeClient();
        return;
    }


};

void Network::updateHost()
{
    sf::Packet pack;
    sf::IpAddress addr;
    sf::Uint16 port;
    currentHost->socket.receive(pack, addr, port);

    Packets::PacketType type = Packets::getPacketType(pack);


    if (type == Packets::AskConnection)
    {
        currentHost->handleClient(addr, port);
    }

    if (type == Packets::SyncPlayerFromClient)
    {
        NetworkSyncPlayerFromClientEvent event;
        event.pack = &pack;
        event.sender_addr = addr;
        event.sender_port = port;
        Events::fire(Events::EventType::NetworkSyncAllFromHostRecieved, &event);
    }

    if (type == Packets::DisconnectFromClient)
    {
        currentHost->disconnectClient(addr);
    }
        
};


void Network::update()
{
    // проверить входящие пакеты и обработать их

    if (isClient())
    {
        updateClient();
    }


    if (isHost())
    {
        updateHost();
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
