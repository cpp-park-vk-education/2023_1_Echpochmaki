#pragma once

#include <map>
#include <vector>
#include <functional>

#include "event.h"


class Events
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

    };


    using EventHandler = std::function<void(Event*)>;

    static void on(EventType type, EventHandler handler)
    ;
    // {
    //     if (events.find(type) == events.end())
    //         events.insert({type, std::vector<EventHandler>()});
        
    //     events[type].push_back(handler);
    // }


    static void fire(EventType type, Event* event)
    ;
    // {
    //     for (auto &handler : events[type])
    //         handler(event);
    // }

private:
    static std::map<EventType, std::vector<EventHandler>> events;

};
