#pragma once
#include <vector>
#include <algorithm>
#include <MyLib/Console_Library/escape_code.h>
#include <MyLib/random_generator.h>
#include <MyLib/random_vector.h>

template<typename T>
using Pair = std::pair<T, T>;

template<typename T>
struct sPoint {
	T x;
	T y;
	sPoint() : x{}, y{} {}
	sPoint(const T& _x, const T& _y = T{}) : x{ _x }, y{ _y } {}

	template<typename U>
	sPoint<U> as() {
		return sPoint<U>(static_cast<U>(x), static_cast<U>(y));
	}
};

namespace Vector_Utility {

	template<typename T, template<typename> class Point>
	T getCoord(const Point<T>& point, int n) {
		T* p = (T*)&point;
		if (n == 0) return *p;
		if (n == 1) return *(p + 1);
		// make assert about 
	}

	template<typename T>
	T getCoord(const std::pair<T, T>& point, int n) {
		T* p = (T*)&point;
		if (n == 0) return *p;
		if (n == 1) return *(p + 1);
	}

	using fPair = Pair<float>;


	// print vector
	template<typename T>
	void printfVec(const std::vector< std::pair<T, T>>& vec)
	{
		int count{};
		std::cout << "--- begin " << vec.size() << " : \n";
		for (auto& v : vec) std::cout << "[" << ++count << "] " << v.first << " , " << v.second << std::endl;
		std::cout << "--- end.\n";
	}
	 
	template<typename T, template<typename> class Point >
	T maxPoints(const std::vector<Point<T>>& vPoint, const int compound_index)
	{
		//	static_assert(compound_index == 0 || compound_index == 1, "Only 0 or 1 accecpted ");
		auto comp = [&](const Point<T>& v1, const Point<T>& v2) {
			return getCoord(v1, compound_index) < getCoord(v2, compound_index);
		};

		auto result = std::max_element(vPoint.begin(), vPoint.end(), comp);

		return getCoord(*result, compound_index);
	}

	template<typename T, template<typename> class Point >
	T minPoints(const std::vector<Point<T>>& vPoint, const int& compound_index)
	{
		//	static_assert(compound_index == 0 || compound_index == 1, "Only 0 or 1 accecpted ");
		auto comp = [&](const Point<T>& v1, const Point<T>& v2) {
			return getCoord(v1, compound_index) < getCoord(v2, compound_index);
		};

		auto result = std::min_element(vPoint.begin(), vPoint.end(), comp);

		return getCoord(*result, compound_index);
	}


	template<typename T, template<typename > class Point = Pair>
	std::array<T, 4> getRect(const std::vector<Point<T>>& p) {
		// get minimum of min_x,min_y; min_x,max_y; ...
		std::array<T, 4> rect;
		rect[0] = minPoints<T, Point>(p, 0);
		rect[1] = minPoints<T, Point>(p, 1);
		rect[2] = maxPoints<T, Point>(p, 0);
		rect[3] = maxPoints<T, Point>(p, 1);

		return rect;
	}

	using pfloat = Pair<float>;

	auto make_random_vec(size_t num, float min1, float max1, float min2, float max2) {
		return vu::make_container<std::vector<pfloat>>(num,
			pfloat{ min1,min2 }, pfloat{ max1,max2 },
			[](pfloat min, pfloat max) { RNG::fRG<float> frand;
		return pfloat(frand(min.first, max.first), frand(min.second, max.second)); });
	}


	std::array<float, 4> getRect(const std::vector<pfloat>& vpfloat) {

		auto max1 = std::max_element(vpfloat.begin(), vpfloat.end(),
			[](const pfloat& pf1, const pfloat& pf2) { return pf1.first <= pf2.first; })->first;
		auto max2 = std::max_element(vpfloat.begin(), vpfloat.end(),
			[](const pfloat& pf1, const pfloat& pf2) { return pf1.second <= pf2.second; })->second;
		auto min1 = std::min_element(vpfloat.begin(), vpfloat.end(),
			[](const pfloat& pf1, const pfloat& pf2) { return pf1.first <= pf2.first; })->first;
		auto min2 = std::min_element(vpfloat.begin(), vpfloat.end(),
			[](const pfloat& pf1, const pfloat& pf2) { return pf1.second <= pf2.second; })->second;

		return std::array<float, 4>{min1, min2, max1, max2};
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    PRINTING CONTAINER THAT EQUIPED BY ITERATOR BEGAN() AND END()
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename Container>
	void print_container(const Container& container, const std::string_view comment ="", int max_width = 35) {
		int i{};
		
		Print_(color::Green, comment) << end_;

		for (auto& element : container) {
			print_ << element << " ";
			++i;
			if (i % max_width == 0) print_ << end_;

			if (i % 11 == 10) std::cin.get();
		}
	}
	 

	template<typename Iter>
	void print_container(Iter first, Iter end, int max_width = 35) {
		int i{};

		for (auto it = first; it != end; ++it) {
			print_ << *it << " ";
			++i;
			if (i % max_width == 0) print_ << end_;
		}
	}

	// OVERLOAD OF PRINT CONTAINER TO POINTER 
	template<typename T>
	void print_container(const T* _array, size_t Size, int max_width = 35) {

		for (size_t i = 0; i != Size; ++i) {
			print_ << _array[i] << " ";
			if ((i+1) % max_width == 0) print_ << end_; 
		}

	}

	// PRINTING CONTAINER OF TYPE MAP<KEY,T> 

	void print_map(const auto comment, const auto& map) {

		std::cout << ESC::Colors::_GREEN_FG << comment << RESETMODE << "{\n";

		for (const auto& pair : map)
			print_ << ESC::Colors::_YELLOW_FG << CELL(15, left, pair.first) << RESETMODE <<
			CELL(10, left, pair.second) << end_;

		print_ << "}\n";
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//     ERASE ELEMENTS FROM VECTOR FROM POSITION pos WITH SIZE size
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	std::vector<T> erase_from_to(const std::vector<T>& vec, size_t pos, size_t size) {

		if (size > vec.size()) {
			Print_(color::Red, "Overflow, check sizing size") << end_;
			return {};
		}

		std::vector<T> v(vec.size() - size);

		std::copy(vec.begin(), vec.begin() + pos, v.begin());
		std::copy(vec.begin() + pos + size, vec.end(), v.begin() + pos);

		return v;
	}

}

#ifndef vu
namespace vu = Vector_Utility;
#endif