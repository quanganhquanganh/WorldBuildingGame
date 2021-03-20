#ifndef TOOLS
#define TOOLS
#include <iostream>
#include <random>
#include <fstream>
#include <vector>

//Random apparatus for randomizing cards descriptions and events----------------------------------------------------------------------

template<typename Engine>
class Random_engine {
public:
	Random_engine() = delete;

	static Engine get_engine() {
		return engine;
	}
	static Engine& engine() {
		return engine;
	}
	static void seed(long n) {
		engine_instance().seed(n);
	}
	static auto get(int begin, int end) {
		std::uniform_int_distribution<> uint(begin, end);
		return uint(static_cast<std::default_random_engine&>(engine_instance()));
	}
protected:
	static Engine& engine_instance() {
		static Engine engine;
		return engine;
	}
};

using basic_random = Random_engine<std::default_random_engine>;

template<typename T>
inline auto rand_element(const std::vector<T>& v) {
	return v[basic_random::get(0, v.size() - 1)];
}

template<typename T>
auto randomized_n_values(std::vector<T> vT, int n) {
	std::vector<T> res_vec;
	auto remove = [&vT](int i) {
		vT[i] = vT[vT.size() - 1]; //Put the last element into the i-th position
		vT.pop_back(); //Pop the last element
	};

	for (int i = 0; i < n; ++i) {
		int rand_index = basic_random::get(0, vT.size() - 1);
		res_vec.push_back(vT[rand_index]);
		remove(rand_index);
	}

	return res_vec;
}

//------------------------------------------------------------------------------------------------------------------------------------

#endif // !TOOLS