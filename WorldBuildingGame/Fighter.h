#pragma once

#include <string>
#include <stack>
#include "Stealth.h"
#include "cards.h"

#ifndef FIGHTER_LIB
#define FIGHTER_LIB

namespace WorldGame {
	using strVec = std::vector<std::string>;
	using Position = unsigned short;
	using Inspirator::Card;
	
	struct next_sqr {//Function object for getting next step from one position to another
		const Map& map;
		next_sqr(const Map& m) : map{ m } {};
		Position operator()(Position a, Position b); //Find next position-step from a to b
	};

	class Enemy {
	public:
		Enemy(){};
		Enemy(const Enemy&);
		Enemy& operator=(const Enemy&);

		void move_into(const Map&);
		void set_card(const Card&);
		void move_card(Card&&);
		
		void next_move(const Map&);

		const Card& get_card() const { return card; };
		Card get_card() { return card; };

	private:
		int HP { 0 };//Enemy's Health
		int dam { 0 };//Enemy's Damage
		Position curPos { 0 };
		std::stack<Position> pLoop; //Enemy's Patrol Loop
		Inspirator::Card card;
	};

	void gen_stats(Enemy&);
	void gen_card(Enemy&);

	std::stack<Position> create_p_loop(const Map&);
}
#endif // !FIGHTER_LIB
