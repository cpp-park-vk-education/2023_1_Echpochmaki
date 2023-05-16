#include "Network.h"
#include "Host.h"
#include "client.h"
#include "Packets.h"
#include "events.h"
#include <iostream>

using std::cout;
using std::endl;

#ifndef INFO
#define INFO __FILE__ << ":" << __LINE__
#endif

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

    Events::on(Events::EventType::SyncSystemClientToHostSendSync, [this](OurEvent *event)
    {
        auto *e = dynamic_cast<SyncSystemSyncEvent*>(event);
        if (isClient())
        {
            currentClient->send(*e->pack);
        }
    });

    Events::on(Events::EventType::SyncSystemHostToClientSendSync, [this](OurEvent *event)
    {
        auto *e = dynamic_cast<SyncSystemSyncEvent*>(event);
        if (isHost())
        {
            currentHost->send(*e->pack);
        }
    });

    cout << "[net] " << INFO << " Network object created" << endl;
};


weak_ptr<IHost> Network::runHost()
{
    // забиндить порт
    cout << "[net] " << INFO << " call runHost" << endl;

    currentHost = std::make_shared<Host>();

    if (currentHost->socket.bind(HOST_PORT) != sf::Socket::Done)
    {
        cout << "  error to bind host socket" << endl;
        currentHost.reset();
    }
    else
    {
        cout << "  socket successfully binded" << endl;
        currentHost->socket.setBlocking(false);
        currentHost->addr = "localhost";
        currentHost->port = currentHost->socket.getLocalPort();
    }

    return weak_ptr<IHost>(currentHost);
};

bool Network::connectToHost(const sf::IpAddress& addr, sf::Uint32 port)
{
    cout << "[net] " << INFO << " call connectToHost " << addr << ":" << port << endl;
    // послать пакет о подключении, дождаться ответа

    currentClient = std::make_shared<Client>();

    if (currentClient->socket.bind(CLIENT_PORT) != sf::Socket::Done)
    {
        std::cout << "  error to bind client socket" << endl;
        currentClient.reset();
        return false;
    }
    else
    {
        std::cout << "  client socket successfully binded" << endl;
        currentClient->socket.setBlocking(false);
        currentClient->addr = addr;
        currentClient->port = currentClient->socket.getLocalPort();
    }

    return currentClient->connectToHost(addr, port);
};

void Network::closeClient()
{
    cout << "[net] " << INFO << " call closeClient isClient()=" << isClient() << endl;
    if (isClient())
    {
        currentClient->disconnect();
        currentClient.reset();
    }
}


void Network::closeHost()
{
    // послать всем пакет о закрытии
    cout << "[net] " << INFO << " call closeHost isHost()=" << isHost() << endl;

    if (isHost())
    {
        currentHost->disconnectAll();
        currentHost.reset();
    }

};

void Network::updateClient()
{
//    cout << "[net] " << INFO << " call updateClient" << endl;

    sf::Packet pack;
    sf::IpAddress addr;
    sf::Uint16 port;
    auto status = currentClient->socket.receive(pack, addr, port);

    if (status != sf::Socket::Done)
    {
        if (status != sf::Socket::NotReady)
            cout << "[net] " << INFO << " packet not received status=" << status;
        return;
    }

    Packets::PacketType type = Packets::getPacketType(pack);
    cout << "[net] " << INFO << "   packet received type=" << type << " size=" << pack.getDataSize() << endl;

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
//    cout << "[net] " << INFO << " call updateHost" << endl;

    sf::Packet pack;
    sf::IpAddress addr;
    sf::Uint16 port;
    auto status = currentHost->socket.receive(pack, addr, port);

    if (status != sf::Socket::Done)
    {
        if (status != sf::Socket::NotReady)
            cout << "[net] " << INFO <<  "   packet not received status=" << status << endl;
        return;
    }

    Packets::PacketType type = Packets::getPacketType(pack);
    cout << "[net] " << INFO <<  "   packet received type=" << type << " size=" << pack.getDataSize() << endl;


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
        Events::fire(Events::EventType::NetworkSyncPlayerFromClientEvent, &event);
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
