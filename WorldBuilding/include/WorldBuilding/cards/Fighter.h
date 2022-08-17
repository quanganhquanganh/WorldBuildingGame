#pragma once

#include <string>
// #include "Stealth.h"
// #include "cards.hpp"
// #include "Skill.h"
// #include "Weapon.hpp"

#ifndef FIGHTER_LIB
#define FIGHTER_LIB

// namespace WorldGame {
// 	using strVec = std::vector<std::string>;
// 	using Position = unsigned short;

// 	class Fighter {
// 	public:
// 		Fighter() = default;
// 		Fighter(const Fighter&);
// 		Fighter& operator=(const Fighter&);

// 		//Actions----------------------------------------------------------------------------
// 		void move_into(const Map&);
// 		void next_move(const Map&);
// 		void look(const Map&);
// 		//------------------------------------------------------------------------------------
		
// 		//Variables access--------------------------------------------------------------------
// 		void move_card(Card&);
// 		auto& card() { return crd; };
// 		const auto& card() const { return crd; }
// 		auto& health() { return HP; }
// 		const auto& health() const { return HP; }
// 		auto& damage() { return dam; }
// 		const auto& damage() const { return dam; }
// 	protected:
// 	private:
// 		int HP { 0 };//Fighter's Health
// 		int dam { 0 };//Fighter's Damage
// 		Position curPos { 0 };//Current Position
// 		std::list<Position> pLoop; //Fighter's Patrol Loop
// 		std::vector<Position> vsion; //Fighter's Vision
// 		Inspirator::Card crd;//Fighter's card
// 	};

// 	namespace Details {
// 		constexpr auto next_pos(Position a, Position b, int side_len);
// 		void gen_stats(WorldGame::Fighter&);
// 		std::list<Position> create_p_loop(const Map&);
// 	}
// }
#endif // !FIGHTER_LIB
