#pragma once
#include <type_traits>
#include "vector_utility1.h"
#include <cmath>


// norm
template<typename T>
inline T norm2d(T x, T y) {
	return std::sqrt(x * x + y * y);
}

template<typename T, template<typename>  class Vector>
T norm2d(const Vector<T>& v) {
	static_assert(std::is_arithmetic<T>::value, "Type should be arithmetic type");
	T x = getCoord(v, 0);
	T y = getCoord(v, 1);
	return std::sqrt(x * x + y * y);
}

template<typename T, template<typename>  class Vector>
T norm2d(const Vector<T>& p1, const Vector<T> p2) {
	static_assert(std::is_arithmetic<T>::value, "Type should be arithmetic type");
	T x1 = getCoord(p1, 0);
	T y1 = getCoord(p1, 1);
	T x2 = getCoord(p2, 0);
	T y2 = getCoord(p2, 1);

	return norm2d<T>(x2-x1,y2-y1);
}


// normal
// direction

// getCoord new style

// xproduct

// vectorial product

// condition of perpendicularity and parallilism

// condition of alignment 3 point

// Find Closed Point to given Points in plan 2d
template<typename T, template<typename > class Vector >
Vector<T> findClosestPoint2d(const Vector<T>& point, const std::vector<Vector<T>>& vPoints) {

	if (vPoints.size() == 0)
	{
		std::cout << "vector of points is empty ---\n";
		return Vector<T>{};
	}

	Vector<T> tmp_point{};
	T tmp_norm = norm2d<T,Vector>(point, vPoints[0]);

	for (auto& p : vPoints)
	{
		T r = norm2d<T,Vector>(point, p);
		if (r < tmp_norm)
		{
			tmp_norm = r;
			tmp_point = p;
		}
	}

	return tmp_point;
}

// Find farest Point from set of points 
template<typename T, template<typename > class Vector >
Vector<T> findFarestPoint2d(const Vector<T>& point, const std::vector<Vector<T>>& vPoints) {

	if (vPoints.size() == 0)
	{
		std::cout << "vector of points is empty ---\n";
		return Vector<T>{};
	}

	Vector<T> tmp_point{};
	T tmp_norm = norm2d<T, Vector>(point, vPoints[0]);

	for (auto& p : vPoints)
	{
		T r = norm2d<T, Vector>(point, p);
		if (r > tmp_norm)
		{
			tmp_norm = r;
			tmp_point = p;
		}
	}

	return tmp_point;
}
