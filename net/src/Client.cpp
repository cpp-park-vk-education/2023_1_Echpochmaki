#include "client.h"
#include "Packets.h"

#include <iostream>

void Client::disconnect() 
{
    connected = false;
    map_received = false;
    waiting_connect_answer = false;
    
    sf::Packet pack;
    pack << sf::Int32(Packets::PacketType::DisconnectFromClient);
    send(pack);
};

bool Client::connectToHost(const sf::IpAddress& addr, sf::Uint16 port)
{
    this->addr = addr;
    this->port = port;
    Packets::sendAskConnection(socket, addr, port);
    waiting_connect_answer = true;
    return true;
};

bool Client::send(sf::Packet& packet) 
{
    std::cout << "[client] send pack to " << addr << ":" << port << " packet.size=" << packet.getDataSize() << std::endl;
    socket.send(packet, addr, port);
    return false;
};
