//
// Created by Андрей on 15.05.2023.
//

#ifndef GAME_2023_1_ECHPOCHMAKI_TIME_TIMER_H_
#define GAME_2023_1_ECHPOCHMAKI_TIME_TIMER_H_

#include <SFML/Graphics.hpp>
using namespace sf;

class Timer
{
 public:
	static Clock& getTimer()
	{
		static Clock timer;
		return timer;
	}

};

#endif //GAME_2023_1_ECHPOCHMAKI_TIME_TIMER_H_
