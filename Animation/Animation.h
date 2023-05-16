//
// Created by Андрей on 03.05.2023.
//

#ifndef ECS_2023_1_ECHPOCHMAKI_ANIMATION_ANIMATION_H_
#define ECS_2023_1_ECHPOCHMAKI_ANIMATION_ANIMATION_H_

#include "IAnimation.h"

class Animation : IAnimation
{
 private:
	std::vector<Frame> frames;
	Sprite& sprite;
	Texture texture;

	const double animationDeltaTime = 0.01;
	const double switchTime = 0.1;
	double totalTime = 0.0f;
	int curFrame = 0;
 public:
	void update(TimeValueType timePassed) override
	{
		totalTime += timePassed;
		if (totalTime >= switchTime)
		{
			totalTime -= switchTime;
			curFrame++;
			sprite.setTextureRect(frames[curFrame].rect);
		}

	}

	Animation(const char* pathToImg, int index,
		unsigned width,
		unsigned height,
		unsigned count,
		TimeValueType duration,
		Sprite& sprite) : sprite(sprite)
	{
		Image img;
		img.loadFromFile(pathToImg);
		int framesCount = 0;
		int x_start = img.getSize().x / width;
		int y_start = img.getSize().y / height;
		while (framesCount < count)
		{
			IntRect rect(x_start, y_start, width, height);
			frames.push_back(Frame(rect, duration / count));
			x_start += width;
			y_start += height;
			framesCount++;
		}

	}

};

enum animationTypes
{
	IDLE, MOVEMENT, DEATH
};

class Animations
{
 private:
	std::vector<IAnimation> animations;
	std::vector<animationTypes> animationNames;
 public:
	void AddAnimation(IAnimation animation, animationTypes animation_type);
	void PlayAnimation(TimeValueType timePassed, animationTypes animationType, RenderWindow& window);

};

#endif //ECS_2023_1_ECHPOCHMAKI_ANIMATION_ANIMATION_H_
