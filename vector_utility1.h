#pragma once
#include <vector>
#include <algorithm>


template<typename T>
using Pair = std::pair<T, T>;

template<typename T>
struct sPoint {
	T x;
	T y;
	sPoint() : x{}, y{} {}
	sPoint(const T& _x, const T& _y) : x{ _x }, y{ _y } {}

	template<typename U>
	sPoint<U> as() {
		return sPoint<U>(static_cast<U>(x), static_cast<U>(y));
	}
};

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
T maxPoints(const std::vector<Point<T>>& vPoint, const int& compound_index)
{
//	static_assert(compound_index == 0 || compound_index == 1, "Only 0 or 1 accecpted ");
	auto comp = [&](const Point<T>& v1, const Point<T>& v2) {
		return getCoord(v1, compound_index) < getCoord(v2, compound_index);
	};

	auto result = std::max_element(vPoint.begin(), vPoint.end(), comp);

	return getCoord(*result,compound_index);
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
std::array<T,4> getRect(const std::vector<Point<T>>& p) {
	// get minimum of min_x,min_y; min_x,max_y; ...
	std::array<T, 4> rect;
	rect[0] = minPoints<T, Point>(p, 0);
	rect[1] = minPoints<T, Point>(p, 1);
	rect[2] = maxPoints<T, Point>(p, 0);
	rect[3] = maxPoints<T, Point>(p, 1);

	return rect;
}