#pragma once

#include <SFML/Network.hpp>
#include <iostream>

class Packets
{
public:
    // пакеты которые просто удобно один раз создать и использовать где надо
    static sf::Packet askConnectionPack;
    static sf::Packet successConnectionPack;

    // static sf::Packet disconnectFromServerPack;

    // первые 4 байта в каждом пакете - целое число со знаком (int), которое обозначает 'тип пакета', то есть как нужно интерпретировать данные в нем
    enum PacketType
    {
        // просто значение для обозначения наименьшего элемента энума, не используется в пакетах
        FirstType = -1,

        // означает, что тип пакета не какой то из валидных типов
        Unknown,

        // тип пакета означает запрос клиента на подключение к серверу
        AskConnection,

        // тип пакета означает успешный ответ сервера на запрос на подключение
        SuccessConnection,

        // тип пакета означает, что хост отправил клиенту сообщение, что его отключают
        DisconnectFromHost,

        // тип пакета означает, что клиент отправил сообщение хосту, что он отключается
        DisconnectFromClient,
    
        // тип пакета с данными о карте, содержит нужную для генерации такой же карты информацию, отправляется от хоста клиенту
        MapGenerationInfo,

        // означает пакет, который отправил хост клиенту, с данными о синхронизации всех сущностей (в том числе локального игрока, эти данные следует игнорировать в sync системе)
        SyncAllEntitiesFromHost,

        // означает пакет, который клиент отправил хосту, с данными о синхронизации игрока
        SyncPlayerFromClient,

        // просто значение для обозначения наибольшего элемента энума, не используется в пакетах
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
