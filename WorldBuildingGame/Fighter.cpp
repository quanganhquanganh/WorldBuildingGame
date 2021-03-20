#include "Fighter.h"

namespace WorldGame {
	Enemy::Enemy(const Enemy& e)
		:HP{ e.HP }, dam{ e.dam }, curPos{e.curPos},
		pLoop{ e.pLoop }, crd{ e.card } {}

	Enemy& Enemy::operator=(const Enemy& e) {
		HP = e.HP;
		dam = e.dam;
		pLoop = e.pLoop;
		crd = e.card;
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

	void Enemy::set_card(const Card& c) {
		crd = c;
	}

	void Enemy::move_card(Card& c) {
		crd = std::move(c);
	}

	namespace Details {
		std::list<Position> create_p_loop(const Map& m) {
			int size = m.get_tiles().size();
			int n = basic_random::get(2, 4);
			auto a = randomized_n_values(m.inner_tiles(), n);
			return std::list<Position>(a.begin(), a.end());
		}

		void gen_stats(Enemy& e) {
			e.health() = basic_random::get(5, 25);
			e.damage() = basic_random::get(5, 20);
		}
	}
}