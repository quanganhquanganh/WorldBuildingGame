#pragma once

#include <string>
#include <queue>
#include "Stealth.h"
#include "cards.h"

#ifndef FIGHTER_LIB
#define FIGHTER_LIB

namespace WorldGame {
	using strVec = std::vector<std::string>;
	
	struct Position {
		int x, y;
	};

	class Enemy {
	public:
		Enemy();
		Enemy(const Enemy&);
		void move_into(const Map&);
		void randomize_power();

	private:
		int HP = 0;//Enemy's Health
		int dam = 0;//Enemy's Damage
		std::queue<Position> pLoop; //Enemy's Patrol Loop
		Inspirator::Card card;
	};
}
#endif // !FIGHTER_LIB
