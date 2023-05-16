#ifndef GAME_SINKABLECOMPONENT_H
#define GAME_SINKABLECOMPONENT_H

#include "../inc/ECS.h"

using TypeId = size_t;

struct  SinkableComponent : public Component {

public:
    TypeId id;

    SinkableComponent(TypeId id) : id(id)
    {
            
    }

};


#endif //GAME_SINKABLECOMPONENT_H
