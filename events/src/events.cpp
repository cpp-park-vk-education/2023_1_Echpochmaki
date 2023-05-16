#include "events.h"


std::map<Events::EventType, std::vector<Events::EventHandler>> Events::events;


void Events::on(EventType type, EventHandler handler)
{
    if (events.find(type) == events.end())
        events.insert({type, std::vector<EventHandler>()});

    events[type].push_back(handler);
    std::cout << "[events] " << INFO << " added new handler(" << handler.target_type().name() << ") to "
                << type << " handlers=" << events[type].size() << std::endl;
//    std::cout << handler.target<>()
}

void Events::fire(EventType type, OurEvent* event)
{
    std::cout << "[events] " << INFO << " fire "
            << type << " handlers=" << events[type].size() << std::endl;
    for (auto &handler : events[type])
        handler(event);
}
