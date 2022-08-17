#include "WorldBuilding/inspirator.hpp"
#include "tools.hpp"
#include <time.h>
#include <fstream>

using std::string;
constexpr char DES_IDENTIFIER[] = "des{";
constexpr char EV_IDENTIFIER[] = "ev{";

std::vector<string> get_des(std::istream& is) {
	std::vector<string> des_list;
	string s;
	char c = 0;
	std::getline(is, s);
	if (s != DES_IDENTIFIER) {
		is.clear(std::ios_base::failbit);
	}
	else {
		string line;
		while (std::getline(is, line) && line != "}") {
			des_list.push_back(line);
		}
	}
	return des_list;
}
std::vector<string> get_ev(std::istream& is) {
	std::vector<string> ev_list;
	string s;
	char c = 0;
	std::getline(is, s);
	if (s != EV_IDENTIFIER) {
		is.clear(std::ios_base::failbit);
	}
	else {
		string line;
		while (std::getline(is, line) && line != "}") {
			ev_list.push_back(line);
		}
	}
	return ev_list;
}

// int main() {
// 	basic_random::seed(static_cast<long>(time(NULL) * time(NULL)));
// 	{
// 		using namespace Inspirator;
// 		std::ifstream ifs{"english.txt"}; 
		
// 		std::vector<string> des_list;
// 		std::vector<string> ev_list;

// 		des_list = get_des(ifs);
// 		ev_list = get_ev(ifs);
		
// 		Card c;
// 		auto cr = card_randomize(des_list, ev_list);
// 		cr(c);
// 		std::cout << c << std::endl;
// 	}
	
// }