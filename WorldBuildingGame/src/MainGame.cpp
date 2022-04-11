#include "Stealth.h"
#include <time.h>

std::ostream& operator<<(std::ostream& os, const WorldGame::Tile::Type& tt) {
	using Type = WorldGame::Tile::Type;
	std::vector<std::string> vT = { "EMPTY", "SAFE", "NORMAL", "WORLD", "CITY", "SHELTER"};
	return os << vT[static_cast<int>(tt)];
}

std::ostream& operator<<(std::ostream& os, const WorldGame::Map& m) {
	auto sl = m.side_len();
	for (int i = 0; i < sl; ++i) {
		for (int j = 0; j < sl; ++j)
			os << m.tiles()[i * (unsigned int)sl + j].type() << "\t";
		os << std::endl;
	}
	return os;
}

int main() {
	using namespace WorldGame;
	basic_random::seed(static_cast<long>(time(NULL) * time(NULL)));

	for (int i = 0; i < 5; ++i) {
		Map testMap(4);
		testMap.worldify();
		std::cout << "Map #" << i << std::endl
				<< testMap << std::endl;
	}
}