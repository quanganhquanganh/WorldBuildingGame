#include "Stealth.h"
#include <cmath>
#include "rand_tools.h"

namespace WorldGame {
	using Type = Tile::Type;

	void SeedGeneration(long l) {
		seed_rand(l);
	}

	Tile::Tile(Type t)
		:tileType{ t } {}
	
	void Map::all_tiles_to(Type t) noexcept{
		for (auto& x : tiles) {
			x.set_type(t);
		}
	}

	auto randomized_n_ints(std::vector<int> vT, int n) {
		std::vector<int> res_vec{};
		auto remove = [&vT](int i) {
			vT[i] = vT[vT.size() - 1]; //Put the last element into the i-th position
			vT.pop_back(); //Pop the last element
		};

		for (int i = 0; i < n; ++i) {
			int rand_index = rand_int(0, vT.size() - 1);
			res_vec.push_back(vT[rand_index]);
			remove(rand_index);
		}

		return res_vec;
	}

	inline int side_len(const Map* const m) noexcept { return sqrt(m->get_tiles().size());}

	auto find_edge_tiles(const Map* const m) noexcept {
		std::vector<int> eT{};
		int sideLen = side_len(m);

		//Add horizontal sides
		for (int i = 0; i < sideLen; ++i) {
			eT.push_back(i);//First row
			eT.push_back(i + sideLen * (sideLen - 1));//Last row
		}

		//Add vertical sides
		for (int i = 1; i < sideLen - 1; ++i) {
			eT.push_back(1 * sideLen);//First column w/out the corner tiles
			eT.push_back((i + 1) * sideLen - 1);//Last column w/out the corner tiles
		}

		return eT;
	}
	auto find_inner_tiles(const Map* const m) noexcept {
		std::vector<int> iT{};
		int sideLen = side_len(m);
		
		for (int i = 1; i < sideLen - 1; ++i) {
			for (int j = i * sideLen + 1; j < (i + 1) * sideLen - 1; ++j) {
				iT.push_back(j);
			}
		}
		return iT;
	}

	void Map::stealthify() {
		constexpr int maxSafeZones{ 5 };
		constexpr Type normalType{ Type::NORMAL };
		constexpr Type safeType{ Type::SAFE };
		
		//Turn into stealth map
		this->all_tiles_to(normalType); 
		this->dT = normalType;

		std::vector<int> edgeTiles{};
		edgeTiles = find_edge_tiles(this);
		auto safe_tiles = randomized_n_ints(edgeTiles, maxSafeZones);

		//Set safe tiles  
		for (auto i : safe_tiles) {	
			tiles[i].set_type(safeType);
		}
	}

	void Map::worldify() {
		constexpr int maxSafeZones{ 5 };
		constexpr int maxCityZones{ 5 };
		constexpr Type normalType{ Type::WORLD };
		constexpr Type cityType{ Type::CITY };
		constexpr Type safeType{ Type::SHELTER };

		this->all_tiles_to(normalType);
		this->dT = normalType;

		std::vector<int> edgeTiles{};
		std::vector<int> innerTiles{};
		edgeTiles = find_edge_tiles(this);
		innerTiles = find_inner_tiles(this);

		auto safe_tiles = randomized_n_ints(edgeTiles, maxSafeZones);
		auto city_tiles = randomized_n_ints(innerTiles, maxCityZones);

		//Set safe tiles  
		for (auto i : safe_tiles) {
			tiles[i].set_type(safeType);
		}
		//Set city tiles  
		for (auto i : city_tiles) {
			tiles[i].set_type(cityType);
		}
	}

	Map::Map(int size)
		:tiles{std::vector<Tile>((size + 1) * (size + 1), dT)} //Map is a square of (size+1)^2, the edge is used for rear tiles
	{}
}