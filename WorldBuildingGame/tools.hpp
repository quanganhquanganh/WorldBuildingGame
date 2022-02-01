#ifndef INSP_TOOLS
#define INSP_TOOLS
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
#include <cassert>

/// Random apparatus for randomizing cards descriptions and events----------------------------------------------------------------------

/// Return True if type T is int
template<typename T>
struct is_int {
	static constexpr bool value =
		std::is_same<T, short>::value
		|| std::is_same<T, int>::value
		|| std::is_same<T, long>::value
		|| std::is_same<T, long long>::value
		|| std::is_same<T, unsigned short>::value
		|| std::is_same<T, unsigned int>::value
		|| std::is_same<T, unsigned long>::value
		|| std::is_same<T, unsigned long long>::value;
};

/// Return True if type T is iterator
template<typename T>
struct is_iterator {
private:
	template <typename A,
		typename = typename std::iterator_traits<A>::difference_type,
		typename = typename std::iterator_traits<A>::pointer,
		typename = typename std::iterator_traits<A>::reference,
		typename = typename std::iterator_traits<A>::value_type,
		typename = typename std::iterator_traits<A>::iterator_category
	> static long test(A&&);

	static constexpr bool test(...);
public:
	static constexpr bool value = std::is_same<decltype(test(std::declval<T>())), long>::value;
};

/// Return True if struct has stl container's characteristics
template<typename T>
struct is_stl_container
{
private:
	typedef typename std::remove_const<T>::type test_type;

	template<typename A>
	static constexpr bool test(
		A* pt,
		A const* cpt = nullptr,
		decltype(pt->begin())* = nullptr,
		decltype(pt->end())* = nullptr,
		decltype(cpt->begin())* = nullptr,
		decltype(cpt->end())* = nullptr,
		typename A::iterator* pi = nullptr,
		typename A::const_iterator* pci = nullptr,
		typename A::value_type* pv = nullptr) {

		typedef typename A::iterator iterator;
		typedef typename A::const_iterator const_iterator;
		typedef typename A::value_type value_type;
		return  std::is_same<decltype(pt->begin()), iterator>::value &&
			std::is_same<decltype(pt->end()), iterator>::value &&
			std::is_same<decltype(cpt->begin()), const_iterator>::value &&
			std::is_same<decltype(cpt->end()), const_iterator>::value &&
			std::is_same<decltype(**pi), value_type&>::value &&
			std::is_same<decltype(**pci), value_type const&>::value;

	}

	template<typename A>
	static constexpr bool test(...) {
		return false;
	}

public:
	static constexpr bool value = test<test_type>(nullptr);
};

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

	static void seed(int n) {
		engine_instance().seed(n);
	}

	template<typename IntType>
	static typename std::enable_if_t<is_int<IntType>::value, IntType> get(IntType begin, IntType end) {
		std::uniform_int_distribution<> uint(begin, end);
		return uint(static_cast<std::default_random_engine&>(engine_instance()));
	}

	template<typename InputIt>
	static typename std::enable_if_t<is_iterator<InputIt>::value
		, InputIt> get(InputIt first, InputIt last) {
		const auto size = std::distance(first, last);
		if (0 == size) return last;
		using diff_t = typename std::iterator_traits<InputIt>::difference_type;
		return std::next(first, get(0, (int)size - 1));
	}

protected:
	static Engine& engine_instance() {
		static Engine engine;
		return engine;
	}
};

using basic_random = Random_engine<std::default_random_engine>;

template<typename Container>
inline typename std::enable_if_t<is_stl_container<Container>::value, typename Container::value_type> const& rand_element(const Container& v) {
	assert(0u != v.size());
	return *basic_random::get(std::begin(v), std::end(v));
}

template<typename T>
auto rnd_vals_no_dupl(std::vector<T> vT, std::size_t n) {
	std::vector<T> res_vec;
	n = std::min(n, vT.size());
	auto remove = [&vT](int i) {
		vT[i] = vT[vT.size() - 1]; //Put the last element into the i-th position
		vT.pop_back(); //Pop the last element
	};

	for (decltype(n) i = 0; i < n; ++i) {
		auto rand_index = basic_random::get(0, (int)vT.size() - 1);
		res_vec.push_back(vT[rand_index]);
		remove(rand_index);
	}

	return res_vec;
}

/*
* Cut a sub square matrix from a linear-like matrix 
* starting from first position to last.
*/
template<typename T>
auto cut_sub_matrix(std::vector<T> vT, std::size_t top_left, std::size_t bottom_right) {
	//Note: top_left and bottom_right are the indices of the top-left and bottom-right corners of the sub matrix
	std::vector<T> res_vec;
	auto side_len = sqrt(vT.size());
	//Check if the indices are valid
	assert(top_left < bottom_right && bottom_right <= side_len * side_len);
	//Get width and height of the sub matrix using side_len
	auto width = (bottom_right - top_left) / side_len;
	auto height = (bottom_right - top_left) / width;

	for (decltype(top_left) i = top_left; i <= bottom_right; ++i) {
		for (decltype(top_left) j = top_left; j <= bottom_right; ++j) {
			res_vec.push_back(vT[i * side_len + j]);
		}
	}
}

/*
	Path-finding algorithm
	(https://en.wikipedia.org/wiki/A*_search_algorithm)
*/
template<typename T>
auto a_star(std::vector<T> vT, std::size_t start, std::size_t end) {
	//TODO: implement
}

//------------------------------------------------------------------------------------------------------------------------------------

#endif // !TOOLS
