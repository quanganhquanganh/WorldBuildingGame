#include "Stealth.h"

namespace WorldGame {
	using Type = Tile::Type;

	Tile::Tile(Type t)
		:tileType{ t } {}
	
	void Map::all_tiles_to(Type t) noexcept{
		for (auto& x : vT) {
			x.type() = t;
		}
	}
	/*
	auto randomized_n_ints(std::vector<int> vT, int n) {
		std::vector<int> res_vec;
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
	

	template<typename T>
	constexpr inline auto cToTid(T val) {
		return static_cast<Map::TileID>(val);
	}
	*/

	std::vector<Map::TileID> Map::edge_tiles() const noexcept {
		std::vector<Map::TileID> eT;
		int sl = (decltype(sl))(this->side_len());

		//Add horizontal sides
		for (auto i = 0; i < sl; ++i) {
			eT.push_back(i);//First row
			eT.push_back(i + sl * (sl - 1));//Last row
		}

		//Add vertical sides
		for (auto i = 1; i < sl - 1; ++i) {
			eT.push_back(i * sl);//First column w/out the corner tiles
			eT.push_back((i + 1) * sl - 1);//Last column w/out the corner tiles
		}

		return eT;
	}
	std::vector<Map::TileID> Map::inner_tiles() const noexcept {
		std::vector<Map::TileID> iT;
		int sl = (decltype(sl))this->side_len();
		
		for (auto i = 1; i < sl - 1; ++i) {
			for (auto j = i * sl + 1; j < (i + 1) * sl - 1; ++j) {
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
		edgeTiles = this->edge_tiles();
		auto safe_tiles = ran_n_values(edgeTiles, maxSafeZones);

		//Set safe tiles  
		for (auto i : safe_tiles) {	
			vT[i].type() = safeType;
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

		auto edgeTiles = this->edge_tiles();
		auto innerTiles = this->inner_tiles();

		auto safe_tiles = ran_n_values(edgeTiles, maxSafeZones);
		auto city_tiles = ran_n_values(innerTiles, maxCityZones);

		//Set safe tiles  
		for (auto i : safe_tiles) {
			vT[i].type() = safeType;
		}
		//Set city tiles  
		for (auto i : city_tiles) {
			vT[i].type() = cityType;
		}
	}

	Map::Map(int size)
		:vT{std::vector<Tile>((unsigned int)pow((size + 1),2), dT)} //Map is a square of (size+1)^2, the edge is used for rear tiles
	{}
}