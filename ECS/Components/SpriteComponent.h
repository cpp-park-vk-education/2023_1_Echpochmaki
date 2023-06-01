//
// Created by Андрей on 03.05.2023.
//

#ifndef PROJECTS_2023_1_ECHPOCHMAKI_ECS_SPRITECOMPONENT_H_
#define PROJECTS_2023_1_ECHPOCHMAKI_ECS_SPRITECOMPONENT_H_


#include "PositionComponent.h"
#include <SFML/Graphics.hpp>

using namespace sf;

struct SpriteComponent : public Component {


public:
    Sprite sprite;
    int drawingPriority;

    SpriteComponent() = default;

    explicit SpriteComponent(const Sprite &spriteSrc) : sprite(spriteSrc) {

    }

    SpriteComponent(const Sprite &spriteSrc, int drawingPriority_) : sprite(spriteSrc),
                                                                     drawingPriority(drawingPriority_) {}


};


#endif //PROJECTS_2023_1_ECHPOCHMAKI_ECS_SPRITECOMPONENT_H_
