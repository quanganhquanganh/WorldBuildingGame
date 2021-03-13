#ifndef RAND_TOOLS
#define RAND_TOOLS
#include <iostream>
#include <random>
#include <fstream>

//Random apparatus for randomizing cards descriptions and events----------------------------------------------------------------------


class Random_engine {	//Modified random engine for saving a seed modifier after destroyed
	std::default_random_engine engine;
public:
	Random_engine() {}

	explicit operator std::default_random_engine&() {
		return engine;
	}

	void seed(int n) {
		engine.seed(n);
	}
};

Random_engine& get_rand() {
	static Random_engine ran;
	return ran;
}

void seed_rand(int n) {
	get_rand().seed(n);
}

template<typename T>
inline auto rand_element(const std::vector<T>& v) {
	std::uniform_int_distribution<> uint(0, v.size() - 1);
	return v[uint(static_cast<std::default_random_engine&>(get_rand()))];
}

inline int rand_int(int begin, int end) {
	std::uniform_int_distribution<> uint(begin, end);
	return uint(static_cast<std::default_random_engine&>(get_rand()));
}

//------------------------------------------------------------------------------------------------------------------------------------

#endif // !RAND_TOOLS