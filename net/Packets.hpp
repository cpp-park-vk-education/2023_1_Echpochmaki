#pragma once

#include <SFML/Network.hpp>
#include <iostream>

class Packets
{
public:
    static sf::Packet askConnectionPack;
    static sf::Packet successConnectionPack;
    // static sf::Packet disconnectFromServerPack;

    enum PacketType
    {
        FirstType = -1,
        Unknown,

        AskConnection,
        SuccessConnection,
        DisconnectFromHost,
        DisconnectFromClient,
    
        LastType,
    };

    // using enum PacketType;

    // static void resolve 

    static void sendAskConnection(sf::UdpSocket& sock, const sf::IpAddress& addr, sf::Uint16 port);
    
    static void sendSuccessConnection(sf::UdpSocket& sock, const sf::IpAddress& addr, sf::Uint16 port);

    // static void sendDisconnect(sf::UdpSocket& sock, const sf::IpAddress& addr, sf::Uint16 port);

    static PacketType getPacketType(sf::Packet& pack);

};

static inline std::ostream& operator<<(std::ostream& ss, Packets::PacketType type)
{
    switch (type)
    {
    case Packets::FirstType:
        ss << "FirstType(utility)";
        break;
    case Packets::Unknown:
        ss << "Unknown";
        break;
    case Packets::AskConnection:
        ss << "AskConnection";
        break;
    case Packets::SuccessConnection:
        ss << "SuccessConnection";
        break;
    case Packets::DisconnectFromHost:
        ss << "DisconnectFromHost";
        break;
    case Packets::DisconnectFromClient:
        ss << "DisconnectFromClient";
        break;
    case Packets::LastType:
        ss << "LastType(utility)";
        break;
    default:
        ss << "NOT_PACKET_TYPE " << int(type);
        break;
    }

    return ss;
}

static inline sf::Packet& operator<<(sf::Packet& ss, Packets::PacketType type)
{
    ss << sf::Int32(type);
    return ss;
}

static inline sf::Packet& operator>>(sf::Packet& ss, Packets::PacketType type)
{
    sf::Int32 i;
    ss >> i;
    type = static_cast<Packets::PacketType>(i);
    return ss;
}
