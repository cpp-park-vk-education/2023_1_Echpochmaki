//
// Created by Андрей on 03.05.2023.
//

#ifndef PROJECTS_2023_1_ECHPOCHMAKI_ECS_SPRITECOMPONENT_H_
#define PROJECTS_2023_1_ECHPOCHMAKI_ECS_SPRITECOMPONENT_H_


#include "PositionComponent.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class SpriteComponent : public Component
{
 private:
	Texture *texture;
	PositionComponent *position;
	Sprite *sprite;
	RenderWindow *window

 public:
	SpriteComponent() = default;
	SpriteComponent(const char* path,const RenderWindow &r_window)
	{
		texture->loadFromFile(path);
		sprite->setTexture(*texture);
		position = nullptr;
		window = r_window;


	}

	void Init() override
	{
		position = &entity->GetComponent<PositionComponent>();

		//TODO::add texture start implementation
	}
	void Update(TimeValueType timePassed) override
	{
		sprite->move(position->GetPosition());
	}

	void Draw() override
	{
		window->draw(*sprite);
	}

	Sprite* GetSprite()
	{
		return sprite;
	}

};



#endif //PROJECTS_2023_1_ECHPOCHMAKI_ECS_SPRITECOMPONENT_H_
