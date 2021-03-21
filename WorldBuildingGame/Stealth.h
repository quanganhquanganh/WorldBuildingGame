#pragma once

#include "tools.h"

#ifndef STEALTH_LIB
#define STEALTH_LIB

namespace WorldGame {
	class Tile {
	public:
		enum class Type {
			EMPTY = 0, SAFE, NORMAL, WORLD, CITY, SHELTER,
		};
		Tile(Type typeForTile);
		constexpr Type get_type() const noexcept { return tileType; };
		constexpr void set_type(Type t) noexcept { tileType = t; }
	private:
		Type tileType;
	};
	
	
	class Map {
	public:
		using TileID = int;

		Map(int size);
		const auto& get_tiles() const noexcept { return tiles; }
		const std::vector<TileID> edge_tiles() const noexcept;
		const std::vector<TileID> inner_tiles() const noexcept;

		inline double side_len() const noexcept { return sqrt(this->get_tiles().size()); }

		void all_tiles_to(Tile::Type t) noexcept;
		void stealthify();
		void worldify();
		//void citify();
	private:
		Tile::Type dT = Tile::Type::EMPTY; //default tile
		std::vector<Tile> tiles;
	};
}

#endif // !STEALTH_LIB
