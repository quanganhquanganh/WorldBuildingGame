#include "Fighter.h"

namespace WorldGame {
	Enemy::Enemy(const Enemy& e)
		:HP{ e.HP }, dam{ e.dam }, curPos{e.curPos},
		pLoop{ e.pLoop }, card{ e.card } {}

	Enemy& Enemy::operator=(const Enemy& e) {
		HP = e.HP;
		dam = e.dam;
		pLoop = e.pLoop;
		card = e.card;
		curPos = e.curPos;
		return *this;
	}
	

	void Enemy::move_into(const Map& m) {
		pLoop = Details::add_p_loop(m);
	}

	void Enemy::set_card(const Card& c) {
		card = c;
	}

	void Enemy::move_card(Card& c) {
		card = std::move(c);
	}

	namespace Details {
		std::list<Position> add_p_loop(const Map& m) {
			int sze = m.get_tiles().size();
			int n = basic_random::get(2, 4);
			std::vector<Position> allPos;
			for (int i = 0; i < sze; i++) allPos.push_back(i);
			allPos = randomized_n_values(allPos, n);

			return std::list<Position>(allPos.begin(), allPos.end());
		}

		void gen_stats(Enemy& e) {
			
		}
	}
}