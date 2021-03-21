#include "Fighter.h"

namespace WorldGame {
	
	Enemy::Enemy(const Enemy& e)
		:HP{ e.HP }, dam{ e.dam }, curPos{e.curPos},
		pLoop{ e.pLoop }, crd{ e.crd } {}

	Enemy& Enemy::operator=(const Enemy& e) {
		HP = e.HP;
		dam = e.dam;
		pLoop = e.pLoop;
		crd = e.crd;
		curPos = e.curPos;
		return *this;
	}
	

	void Enemy::move_into(const Map& m) {
		pLoop = Details::create_p_loop(m);
		//Get current position from loop 
		//then pop it from list
		curPos = pLoop.front(); 
		pLoop.pop_front();
		//Add the position to the end of the list 
		//assigning the enemy to go back at end of patrol
		pLoop.push_back(curPos);
	}

	void Enemy::move_card(Card& c) {
		crd = std::move(c);
	}

	namespace Details {
		constexpr inline auto coord(Position p, int sidelen) {
			std::array<double, 2> xy{ { 0,0 } };
			auto x = xy[0] = p % sidelen;
			xy[1] = (p - x) / sidelen;
			return xy;
		}
		constexpr inline auto pos(double x, double y, int side_len) {
			return static_cast<Position>(x) + 
				static_cast<Position>(y) * side_len;
		}

		constexpr Position next_pos(Position p1, Position p2, int side_len) {
			auto c1 = coord(p1, side_len);
			auto c2 = coord(p2, side_len);
			//Solve for ax + b = y for p1 and p2
			auto a = (c2[1] - c1[1]) / (c2[0] - c1[0]);
			auto b = c1[1] - a * c1[0];

			auto x = c1[0] + 1;
			auto y = a * x + b;

			return pos(x, y, side_len);
		}

		std::list<Position> create_p_loop(const Map& m) {
			int size = m.get_tiles().size();
			int n = basic_random::get(2, 4);
			auto a = ran_n_values(m.inner_tiles(), n);
			return std::list<Position>(a.begin(), a.end());
		}

		void gen_stats(Enemy& e) {
			e.health() = basic_random::get(5, 25);
			e.damage() = basic_random::get(5, 20);
		}
	}
}