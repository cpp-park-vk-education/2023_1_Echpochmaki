#include "Packets.h"

sf::Packet Packets::askConnectionPack = [] {
    sf::Packet pack;
    pack << sf::Int32(Packets::AskConnection);
    return pack;
}();
    
sf::Packet Packets::successConnectionPack = [] {
    sf::Packet pack;
    pack << sf::Int32(Packets::SuccessConnection);
    return pack;
}();

Packets::PacketType Packets::getPacketType(sf::Packet& pack)
{
    sf::Int32 type;
    pack >> type;
    if (type > FirstType && type < LastType)
        return static_cast<PacketType>(type);
    return Unknown;
}

void Packets::sendCreateRemotePlayerPacket(Entity *player, std::shared_ptr<IClient> client)
{
    sf::Packet pack;
    pack << AddRemotePlayer;

    client->send(pack);
}

void Packets::sendAskConnection(sf::UdpSocket& sock, const sf::IpAddress& addr, sf::Uint16 port)
{
    // sf::Packet pack;
    // pack << sf::Int32(AskConnection);
    sock.send(Packets::askConnectionPack, addr, port);
}

void Packets::sendSuccessConnection(sf::UdpSocket& sock, const sf::IpAddress& addr, sf::Uint16 port)
{
    // sf::Packet pack;
    // pack << sf::Int32(SuccessConnection);
    sock.send(successConnectionPack, addr, port);
}

// void Packets::sendDisconnect(sf::UdpSocket& sock, const sf::IpAddress& addr, sf::Uint16 port)
// {
//     sf::Packet pack;
//     pack << sf::Int32(Disconnect);
//     sock.send(pack, addr, port);
// }