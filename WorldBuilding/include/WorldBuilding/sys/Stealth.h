// #pragma once

// #include "tools.hpp"

// #ifndef STEALTH_LIB
// #define STEALTH_LIB

// namespace WorldGame {
// 	class Tile {
// 	public:
// 		enum class Type {
// 			EMPTY = 0, SAFE, NORMAL, WORLD, CITY, SHELTER,
// 		};
// 		Tile(Type typeForTile);
// 		auto& type() noexcept { return tileType; }
// 		constexpr Type type() const noexcept { return tileType; }

// 	private:
// 		Type tileType;
// 	};
	
	
// 	class Map {
// 	public:
// 		using TileID = int;

// 		Map(int size);
// 		auto& tiles() noexcept { return vT; }
// 		constexpr auto& tiles() const noexcept { return vT; }
// 		std::vector<Map::TileID> edge_tiles() const noexcept;
// 		std::vector<Map::TileID> inner_tiles() const noexcept;

// 		inline double side_len() const noexcept { return sqrt(this->tiles().size()); }

// 		void all_tiles_to(Tile::Type t) noexcept;
// 		void stealthify();
// 		void worldify();
// 		//void citify();
// 	private:
// 		Tile::Type dT = Tile::Type::EMPTY; //default tile
// 		std::vector<Tile> vT;
// 	};
// }

// #endif // !STEALTH_LIB
