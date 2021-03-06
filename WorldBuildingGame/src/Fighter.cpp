#include "Fighter.h"

namespace WorldGame {
	namespace Details {
		class coord {
			double arr[2];
		public:
			constexpr auto operator()(Position p, int sidelen) {
				double x = p % sidelen, y = (p - x) / sidelen;
				arr[0] = x; arr[1] = y;
				return arr;
			}
		};

		constexpr inline auto pos(double x, double y, int side_len) {
			return static_cast<Position>(x) +
				static_cast<Position>(y) * side_len;
		}

		constexpr auto next_pos(Position p1, Position p2, int side_len) {
			auto c1 = coord()(p1, side_len);
			auto c2 = coord()(p2, side_len);
			//Solve for ax + b = y for p1 and p2
			auto a = (c2[1] - c1[1]) / (c2[0] - c1[0]);
			auto b = c1[1] - a * c1[0];

			auto x = c1[0] + 1;
			auto y = a * x + b;

			return pos(x, y, side_len);
		}

		std::list<Position> create_p_loop(const Map& m) {
			auto size = m.tiles().size();
			int n = basic_random::get(2, 4);
			auto a = rnd_vals_no_dupl(m.inner_tiles(), n);
			return std::list<Position>(a.begin(), a.end());
		}

		void gen_stats(Fighter& e) {
			e.health() = basic_random::get(5, 25);
			e.damage() = basic_random::get(5, 20);
		}
	}

	Fighter::Fighter(const Fighter& e)
		:HP{ e.HP }, dam{ e.dam }, curPos{e.curPos},
		pLoop{ e.pLoop }, crd{ e.crd } {}

	Fighter& Fighter::operator=(const Fighter& e) {
		HP = e.HP;
		dam = e.dam;
		pLoop = e.pLoop;
		crd = e.crd;
		curPos = e.curPos;
		return *this;
	}
	/*
		Returns a list of ids of surrounding tiles
		of the tile with id id
	*/
	auto sur_ids = [](int id, const Map& m) {
		
		auto size = (int)sqrt(m.tiles().size());
		auto x = id % size;
		auto y = (id - x) / size;
		auto ids = std::vector<int>{};
		ids.reserve(4);
		if (x > 0) ids.push_back(id - 1);
		if (x < size - 1) ids.push_back(id + 1);
		if (y > 0) ids.push_back(id - size);
		if (y < size - 1) ids.push_back(id + size);
		return ids;
	};

	void Fighter::move_into(const Map& m) {
		pLoop = Details::create_p_loop(m);
		//Get current position from loop 
		//then pop it from list
		curPos = pLoop.front(); 
		pLoop.pop_front();
		//Add the position to the end of the list 
		//assigning the Fighter to go back at end of patrol
		pLoop.push_back(curPos);

	}

	void Fighter::move_card(Card& c) {
		crd = std::move(c);
	}

	template<class T>
	using remove_const_ref_t = typename std::remove_const_t <std::remove_reference_t<T>>;

	template<class T>
	using remove_const_ref_ptr_t = typename std::remove_const_t <std::remove_reference_t<T>>*;

	void Fighter::look(const Map& m) {
		auto& tiles = m.tiles();
		remove_const_ref_t<decltype(tiles)> sT; //Surrounding tiles
		
		auto sI = sur_ids(curPos, m);
		for (auto i : sI) {
			sT.push_back(tiles[i]);
		}
	}

	void Fighter::next_move(const Map& m) {
		this->look(m);
		auto np = this->pLoop.front();//Get next target and
		if (this->curPos == np) {//pop if already reached the target
			this->pLoop.pop_front();
			np = this->pLoop.front();
		}
		this->curPos = Details::next_pos(curPos, np, (int)m.side_len());
	}

	
}