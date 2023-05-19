//
// Created by User on 04.05.2023.
//

#ifndef MAP_GENERATION_IROOMGENERATOR_H
#define MAP_GENERATION_IROOMGENERATOR_H

#include <iostream>
#include <vector>
#include "../../ECS/inc/Tile.h"

// Все спрайты энтити
// Возвращаю матрицу тайлов на всю карту

struct RoomDescriptionBase {
    int width;
    int height;

    RoomDescriptionBase(int width_, int height_) : width(width_), height(height_) {}

    RoomDescriptionBase() = default;
};

class IRoomGenerator {
public:
    virtual tileMap generateRoom(const RoomDescriptionBase &parameters) = 0;

    virtual ~IRoomGenerator() = default;
};

#endif //MAP_GENERATION_IROOMGENERATOR_H
