#ifndef TOOLS
#define TOOLS
#include <iostream>
#include <random>
#include <fstream>
#include <vector>
#include <utility>
#include <iterator>
#include <string>
#include <array>
#include <cmath>
#include <list>
#include <memory>
#include <algorithm>

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
inline auto& rand_element(std::initializer_list<T> v) {
	return v[basic_random::get(0, v.size() - 1)];
}

template<typename T>
auto ran_n_values(std::initializer_list<T> vT, std::size_t n) {
	std::vector<T> res_vec;
	n = std::min(n, vT.size());
	auto remove = [&vT](int i) {
		vT[i] = vT[vT.size() - 1]; //Put the last element into the i-th position
		vT.pop_back(); //Pop the last element
	};

	for (decltype(n) i = 0; i < n; ++i) {
		auto rand_index = basic_random::get(0, vT.size() - 1);
		res_vec.push_back(vT[rand_index]);
		remove(rand_index);
	}

	return res_vec;
}

/*
* Cut a sub matrix from a linear-like matrix 
* starting from first position to last.
*/
template<class InputIt,  //Template for input iterator
		typename Length = std::_Iter_diff_t<InputIt>>
auto sub_matrix_indexes_vector(const InputIt& f, const InputIt& l, Length len) {
	auto dis = std::distance(f, l);
	auto row = std::ceil(dis / len);
	auto col = dis % len;

	std::vector<decltype(dis)>sub_m;
	
	for (decl)
		for (auto y = f_y; y < l_y; ++y)
			sub_m.push_back(x + y * len);

	return sub_m;
}

//------------------------------------------------------------------------------------------------------------------------------------

#endif // !TOOLS