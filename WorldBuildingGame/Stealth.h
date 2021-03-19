#pragma once

#include <string>
#include <vector>
#include "rand_tools.h"

#ifndef STEALTH_LIB
#define STEALTH_LIB

namespace WorldGame {
	class Tile {
	public:
		enum class Type {
			EMPTY = 0, SAFE, NORMAL, WORLD, CITY, SHELTER,
		};
		Tile(Type typeForTile);
		Type get_type() const noexcept { return tileType; };
		void set_type(Type t) noexcept { tileType = t; }
	private:
		Type tileType;
	};
	
	
	class Map {
	public:
		Map(int size);
		const auto& get_tiles() const noexcept { return tiles; }
		inline int side_len() const noexcept { return sqrt(this->get_tiles().size()); }

		void all_tiles_to(Tile::Type t) noexcept;
		void stealthify();
		void worldify();
		//void citify();
	private:
		Tile::Type dT = Tile::Type::EMPTY; //default tile
		std::vector<Tile> tiles;
	};

	void seed_gen(long);
}

#endif // !STEALTH_LIB
