#pragma once
#include <type_traits>
#include <cmath>
#include "vector_utility1.h"


namespace geom2d {

	template<typename T>
	constexpr T Norm(T x, T y) {
		return x * x + y * y;
	}

	template<typename Point>
	constexpr typename Point::value_type Norm(const Point& p) {
		return Norm(p.x, p.y);
	}

	template<typename T>
	constexpr T norm2d(T x, T y) {
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

		return norm2d<T>(x2 - x1, y2 - y1);
	}


	template<typename T, template<typename > class Vector >
	Vector<T> findClosestPoint2d(const Vector<T>& point, const std::vector<Vector<T>>& vPoints) {

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

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //    COLLISIONS BETWEEN TWO OBJECT AND VECTOR OF TWO OBJECT
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	bool IsCloser(T x1, T y1, T x2, T y2, T r) { 
		return Norm<T>(x1 - x2, y1 - y2) <= r * r;
	}

	template<typename Point, typename T = typename Point::value_type>
	bool IsCloser(Point p1, Point p2, T  r)
	{
		return IsCloser<T>(p1.x, p1.y, p2.x, p2.y, r);
	}

	template<typename vType_1, typename Type_2, typename T = typename Type_2::value_type>
	bool Collision(const vType_1& v, const Type_2& p, T r) {

		for (auto& e : v) {
			if (IsCloser(e.get_position(), p.get_position(), r)) {
				return true;
			}
		}

		return false;
	}
}