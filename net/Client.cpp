#include "Client.hpp"
#include "packets.hpp"

void Client::disconnect() 
{
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
