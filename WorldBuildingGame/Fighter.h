#pragma once

#include <string>
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

		//Actions----------------------------------------------------------------------------
		void move_into(const Map&);
		void next_move(const Map&);
		void look(const Map&);
		//------------------------------------------------------------------------------------
		
		//Variables access--------------------------------------------------------------------
		void move_card(Card&);
		auto& card() { return crd; };
		const auto& card() const { return crd; }
		auto& health() { return HP; }
		const auto& health() const { return HP; }
		auto& damage() { return dam; }
		const auto& damage() const { return dam; }
		//------------------------------------------------------------------------------------

	protected:
	private:
		int HP { 0 };//Enemy's Health
		int dam { 0 };//Enemy's Damage
		Position curPos { 0 };//Current Position
		std::list<Position> pLoop; //Enemy's Patrol Loop
		std::vector<Position> vsion; //Enemy's Vision
		Inspirator::Card crd;//Enemy's card
	};

	namespace Details {
		constexpr auto next_pos(Position a, Position b, int side_len);
		void gen_stats(WorldGame::Enemy&);
		std::list<Position> create_p_loop(const Map&);
	}
}
#endif // !FIGHTER_LIB
