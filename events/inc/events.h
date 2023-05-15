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
        MouseInput,
        KeyboardInput,
        NetSend,
        NetReceive,
        GameLoaded,
    };

    using EventHandler = std::function<void(Event*)>;

    static void on(EventType type, EventHandler handler)
    // ;
    {
        if (events.find(type) == events.end())
            events.insert({type, std::vector<EventHandler>()});
        
        events[type].push_back(handler);
    }


    static void fire(EventType type, Event* event)
    // ;
    {
        for (auto &handler : events[type])
            handler(event);
    }

private:
    static std::map<EventType, std::vector<EventHandler>> events;

};
