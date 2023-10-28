#pragma once
#include <ratio>
#include <utility>


namespace rn {

	constexpr std::pair<intmax_t, intmax_t> Ratio(intmax_t _Nx, intmax_t _Dx) {

		intmax_t num = std::_Sign_of(_Nx) * std::_Sign_of(_Dx) * std::_Abs(_Nx) / std::_Gcd(_Nx, _Dx);
		intmax_t den = std::_Abs(_Dx) / std::_Gcd(_Nx, _Dx);

		return std::pair<intmax_t, intmax_t>(num, den);
	}



	constexpr bool isPrim(intmax_t a, intmax_t b) {

		auto r = Ratio(a, b);

		if (r.first == a && r.second == b) return true;

		return false;
	}



}