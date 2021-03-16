#pragma once

#include <string>
#include <queue>
#include "Stealth.h"
#include "cards.h"

#ifndef FIGHTER_LIB
#define FIGHTER_LIB

namespace WorldGame {
	using strVec = std::vector<std::string>;
	using Position = unsigned short;
	using Inspirator::Card;

	class Enemy {
	public:
		Enemy(){};
		Enemy(const Enemy&);
		Enemy& operator=(const Enemy&);

		void move_into(const Map&);
		void set_card(const Card&);
		void move_card(Card&&);

		const Card& get_card() const { return card; };
		Card get_card() { return card; };

	private:
		int HP { 0 };//Enemy's Health
		int dam { 0 };//Enemy's Damage
		Position curPos { 0 };
		std::queue<Position> pLoop; //Enemy's Patrol Loop
		Inspirator::Card card;
	};

	void gen_stats(Enemy&);
	void gen_card(Enemy&);

	std::queue<Position> create_p_loop(const Map&);
}
#endif // !FIGHTER_LIB
