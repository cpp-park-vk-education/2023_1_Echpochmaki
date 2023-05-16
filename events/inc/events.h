#pragma once

#include <map>
#include <vector>
#include <functional>

#include "event.h"
#include <iostream>

#ifndef INFO
#define INFO __FILE__ << ":" << __LINE__
#endif


class   Events
{
public:
    enum class EventType
    {
        // (сейчас не используется) триггерится, когда происходит событие мыши - нажатие, движение
        MouseInput,

        // (сейчас не используется) триггерится, когда происходит событие клавиатуры - нажатие клавиши 
        KeyboardInput,

        // (сейчас не используется) триггерится, когда текущее приложение отправляет данные куда то
        NetSend,

        // (сейчас не используется) триггерится, когда текущее приложение получает данные откуда то
        NetReceive,

        // (сейчас не используется) триггерится после загрузки уровня, текстур, и прочего, то есть когда уже игрок может двигаться и играть
        GameLoaded,

        // ивент триггерится, когда ты клиент, подключился к хосту, и с хоста пришли данные о карте
        MapInfoFromNetReceived,

        // ивент триггерится, когда ты клиент и с хоста пришли данные для синхронизации всех сущностей
        NetworkSyncAllFromHostRecieved,

        // ивент триггерится когда ты хост и с клиента пришел пакет с данными об игроке
        NetworkSyncPlayerFromClientEvent,

        // ивент триггерится внутри sync системы когда ты хост и хочешь отправить данные для синхронизации на клиенты
        SyncSystemHostToClientSendSync,

        // ивент триггерится внутри sync системы когда ты клиент и хочешь отправить данные для синхронизации(в основном данные о локальном игроке) на хост
        SyncSystemClientToHostSendSync,

        // триггерится когда пришел пакет с набором сущностей, которые надо удалить
        NetworkDeleteEntitiesByIds,

        // триггерится чтобы отправить пакет с сущностями, которые надо удалить
        NetworkDeleteEntitiesByIdsSend,

    };


    using EventHandler = std::function<void(OurEvent*)>;

    static void on(EventType type, EventHandler handler)
    ;
    // {
    //     if (events.find(type) == events.end())
    //         events.insert({type, std::vector<EventHandler>()});
        
    //     events[type].push_back(handler);
    // }


    static void fire(EventType type, OurEvent* event)
    ;
    // {
    //     for (auto &handler : events[type])
    //         handler(event);
    // }

private:
    static std::map<EventType, std::vector<EventHandler>> events;

};

static inline std::ostream& operator<<(std::ostream& os, Events::EventType type)
{
//    using enum Events::EventType;      // using enum только с++20
    switch (type) {
        case Events::EventType::MouseInput:
            os << "MouseInput";
            break;
        case Events::EventType::KeyboardInput:
            os << "KeyboardInput";
            break;
        case Events::EventType::NetSend:
            os << "NetSend";
            break;
        case Events::EventType::NetReceive:
            os << "NetReceive";
            break;
        case Events::EventType::GameLoaded:
            os << "GameLoaded";
            break;
        case Events::EventType::MapInfoFromNetReceived:
            os << "MapInfoFromNetReceived";
            break;
        case Events::EventType::NetworkSyncAllFromHostRecieved:
            os << "NetworkSyncAllFromHostRecieved";
            break;
        case Events::EventType::NetworkSyncPlayerFromClientEvent:
            os << "NetworkSyncPlayerFromClientEvent";
            break;
        case Events::EventType::SyncSystemHostToClientSendSync:
            os << "SyncSystemHostToClientSendSync";
            break;
        case Events::EventType::SyncSystemClientToHostSendSync:
            os << "SyncSystemClientToHostSendSync";
            break;
        case Events::EventType::NetworkDeleteEntitiesByIds:
            os << "NetworkDeleteEntitiesByIds";
            break;
        case Events::EventType::NetworkDeleteEntitiesByIdsSend:
            os << "NetworkDeleteEntitiesByIdsSend";
            break;
        default:
            os << "NOT_AN_EVENT_TYPE " << int(type);
            break;
    }
    return os;
}