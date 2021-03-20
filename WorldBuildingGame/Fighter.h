#pragma once

#include <string>
#include <list>
#include <memory>
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
		void move_card(Card&);
		
		void next_move(const Map&);

		const Card& get_card() const { return card; };
		Card get_card() { return card; };
	protected:
		void look(const Map&);
	private:
		int HP { 0 };//Enemy's Health
		int dam { 0 };//Enemy's Damage
		Position curPos { 0 };
		std::list<Position> pLoop; //Enemy's Patrol Loop
		std::shared_ptr<Map> m;
		Inspirator::Card card;
	};

	namespace Details {
		Position get_next_pos(Position a, Position b, int side_len);
		void gen_stats(WorldGame::Enemy&);
		std::list<Position> add_p_loop(const Map&);
	}
}
#endif // !FIGHTER_LIB
