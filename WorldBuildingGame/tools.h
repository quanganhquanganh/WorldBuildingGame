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
inline auto& rand_element(const std::vector<T>& v) {
	return v[basic_random::get(0, v.size() - 1)];
}

template<typename T>
auto ran_n_values(std::vector<T> vT, std::size_t n) {
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
template<class Container, //Template for matrix container
		class First,  //Template for first iterator
		class Last,	//Template for last iterator
		typename Length = int>
auto sub_matrix_indexes_vector(const Container& m, const First& f, const Last& l, Length len) {
	auto f_dis = std::distance(std::begin(m), f);
	auto l_dis = std::distance(std::begin(m), l);

	auto f_x = f_dis % len;
	auto l_x = l_dis % len;

	auto f_y = std::floor(f_dis / len);
	auto l_y = std::floor(l_dis / len);

	std::vector<decltype(f_x)>sub_m;
	
	for (auto x = f_x; x < l_x; ++x)
		for (auto y = f_y; y < l_y; ++y)
			sub_m.push_back(x + y * len);

	return sub_m;
}

//------------------------------------------------------------------------------------------------------------------------------------

#endif // !TOOLS