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
	}

	std::queue<Position> create_p_loop(const Map& m) {

	}

	void Enemy::move_into(const Map& m) {
		pLoop = create_p_loop(m);
	}

	void Enemy::set_card(const Card& c) {
		card = c;
	}

	void Enemy::move_card(Card&& c) {
		card = std::move(c);
	}
}