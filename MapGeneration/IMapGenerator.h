#ifndef MAP_GENERATION_IMAPGENERATOR_H
#define MAP_GENERATION_IMAPGENERATOR_H

#include <iostream>
#include <vector>
#include <memory>
#include "IRoomGenerator.h"
#include "../ECS/Tile.h"

struct MapDescriptionBase{
    int width;
    int height;
};

class IMapGenerator{
public:
    virtual tileMap generateMap(const MapDescriptionBase& parameters) = 0;
    virtual void setRoomGenerator(std::unique_ptr<IRoomGenerator> generator) = 0;

    virtual ~IMapGenerator() = default;
};

#endif //MAP_GENERATION_IMAPGENERATOR_H
