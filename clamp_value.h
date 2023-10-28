#pragma once
#include <limits>

template< typename T>
class ClampValue {
	static_assert(std::is_arithmetic<T>::value, "T should be arithmetic type");
	T x;
	T lo;
	T up;

	void clamp() {
		x = (x < lo) ? lo : (x > up) ? up : x;
	}

public:
	// ClampValue() :x{ T{} }, up{std::numeric_limits<T>::max()}, lo{std::numeric_limits<T>::min()} {}
	ClampValue(const T& _x):x{_x} {}
	explicit ClampValue(const T& _lo, const T& _up) : x{T{}}, lo{_lo}, up{_up} {}

	ClampValue& operator = (const T& _x) { x = _x; clamp(); return *this; }

	operator const T& () {
		clamp();
		return x;
	}

	void setClampValue(const T& _lo, const T& _up) {
		lo = _lo;
		up = _up;
	}
};