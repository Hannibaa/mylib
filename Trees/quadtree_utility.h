#pragma once
#include <type_traits>
#include <iomanip>
#include "C:\Users\Acer\source\MyLib\vector_utility1.h"

// Basic Rectangle 
template<typename T>
struct _Rect {
	static_assert(std::is_arithmetic<T>::value, "type should be arithmetic");
	T x;
	T y;
	T width;
	T height;
};

// Rectangle area for Boundary of spacial information
template<typename T>
struct Rect   {
	static_assert(std::is_arithmetic<T>::value, "type should be arithmetic");
	T x;
	T y;
	T width;
	T height;

	Rect()
		: x{}, y{}, width{}, height{}
	{}

	Rect(T _x, T _y, T _w, T _h)
		:x{ _x }, y{ _y }, width{ _w }, height{ _h }
	{}

	template<typename U>
	Rect<U> as() {

		U _x = static_cast<U>(x);
		U _y = static_cast<U>(y);
		U _width = static_cast<U>(width);
		U _height = static_cast<U>(height);

		return Rect<U>(_x, _y, _width, _height);
	}

	void clear() {
		x = T{};
		y = T{};
		width = T{};
		height = T{};
	}

	template<template<typename> class Point>
    bool contain(const Point<T>& point)
	{
		auto X = getCoord(point, 0);
		auto Y = getCoord(point, 1);
		return x <= X && X <= x + width &&
			y <= Y && Y <= y + height;
	}

	template<template<typename> class Point>
	Point<T> getCenter() {
		//Point<T> p = { x + width / T(2), y + height / T(2) };
		return Point<T>{x + width / T(2), y + height / T(2)};
	}
};

//  Print Rectangle 
template<typename T>
std::ostream& operator << (std::ostream& os, const Rect<T>& rect) {
	os << std::setw(12) << std::left  << "Rect : " << rect.x << " , " << rect.y  
		<< std::fixed 
		 << std::setw(15) << std::right  << " width " << rect.width << " height " << rect.height;
	return os;
}

template<typename T>
class SubRects {
	uint32_t number_w;
	uint32_t number_h;
	std::vector<Rect<T>> vRect;

	void makeSubRect() {

	}

public:
	SubRects() = default;
	SubRects(const Rect<T>& rect, uint32_t n_w, uint32_t n_h)
		: number_w{n_w}, number_h{n_h}
	{
		T w = rect.width / T(n_w);
		T h = rect.height / T(n_h);
		for (uint32_t i = 0; i < n_w ; i++)
			for ( uint32_t j = 0; j < n_h; j++)
		    {
			      vRect.emplace_back(rect.x + i * w, rect.y + j * h, w, h);
		    }
	}

	template<typename U>
	friend std::ostream& operator << (std::ostream& os, const SubRects<U>& srect);
};

//  Print  all sub rectangle
template<typename T>
std::ostream& operator << (std::ostream& os, const SubRects<T>& srect) {
	int i{};
	for (auto& rect : srect.vRect)
		os << std::setw(5) << std::left << ++i << rect << '\n';

	return os;
}