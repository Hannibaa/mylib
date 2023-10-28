#pragma once
#include "bitwisefunction.h"
// make structure of bit mask of data

#define makeBitMask make_bitMask 

template<typename T,int from,int to,bool b = (to < 8*sizeof(T) && from < to) >
constexpr T make_bitMask() {
//	if (!b) { std::cout << "out of range of size of type\n"; return T{}; }
	static_assert(b, "out of range of size of type");

	T x{};
	Byte* pbyte = (Byte*)&x;

	for (int i = from; i < to + 1; i++) {

	      int _i = i / 8;
	      int __i = i % 8;
	      *(pbyte + _i) = *(pbyte + _i) | (1 << __i);
	}

	return x;
};
