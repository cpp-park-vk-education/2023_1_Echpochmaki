//
// Created by Андрей on 03.05.2023.
//

#ifndef ECS_2023_1_ECHPOCHMAKI_ECS_ANIMATIONCOMPONENT_H_
#define ECS_2023_1_ECHPOCHMAKI_ECS_ANIMATIONCOMPONENT_H_

#include "SpriteComponent.h"



struct Frame
{
	IntRect rect;
	TimeValueType duration;
};





class AnimationComponent : public Component
{
 private:
	SpriteComponent *spriteComponent;
	Texture animationTexture;
	TimeValueType timePassed;





 public:
	AnimationComponent() = default;
	AnimationComponent(const char* pathToAnimation)
	{
		animationTexture.loadFromFile(pathToAnimation);
	}




	void Init() override
	{
		spriteComponent = &entity->GetComponent<SpriteComponent>();

	}
	void Update(TimeValueType timePassed) override
	{

	}

	void Draw() override
	{
		window->draw(*sprite);
	}

};

#endif //ECS_2023_1_ECHPOCHMAKI_ECS_ANIMATIONCOMPONENT_H_
