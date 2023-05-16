#ifndef GAME_SINKABLECOMPONENT_H
#define GAME_SINKABLECOMPONENT_H

#include "../inc/ECS.h"


struct SinkableComponent : public Component {

public:
    int id;

    SinkableComponent(int id) : id(id)
    {
            
    }

};


#endif //GAME_SINKABLECOMPONENT_H
