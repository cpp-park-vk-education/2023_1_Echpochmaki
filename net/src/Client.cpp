#include "client.h"
#include "Packets.h"

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
    Packets::sendAskConnection(socket, addr, port);
    waiting_connect_answer = true;
    return true;
};

bool Client::send(sf::Packet& packet) 
{
    socket.send(packet, addr, port);
    return false;
};
