#include "Stealth.h"
#include <iostream>
#include <time.h>
#include <vector>

std::ostream& operator<<(std::ostream& os, const WorldGame::Tile::Type& tt) {
	using Type = WorldGame::Tile::Type;
	std::vector<std::string> vT = { "EMPTY", "SAFE", "NORMAL", "WORLD", "CITY", "SHELTER"};
	return os << vT[static_cast<int>(tt)];
}

std::ostream& operator<<(std::ostream& os, const WorldGame::Map& m) {
	int sideLen = sqrt(m.get_tiles().size());
	for (int i = 0; i < sideLen; ++i) {
		for (int j = 0; j < sideLen; ++j)
			os << m.get_tiles()[i * sideLen + j].get_type() << "\t";
		os << std::endl;
	}
	return os;
}

int main() {
	using namespace WorldGame;
	SeedGeneration(time(NULL) * time(NULL));
	for (int i = 0; i < 5; ++i) {
		Map testMap(12);
		testMap.worldify();
		std::cout << "Map #" << i << std::endl
				<< testMap << std::endl;
	}
}