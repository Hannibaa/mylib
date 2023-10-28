#pragma once
#include <utility>
#include <string>

using uchar = unsigned char;
using ushort = unsigned short;
using uint = unsigned int;

// color Macro
#define _RED(x)       (uchar)(x & 0x000000ff)
#define _GREEN(x)     (uchar)((x & 0x0000ff00) >> 8 )
#define _BLUE(x)      (uchar)((x & 0x00ff0000) >> 16 )

#define _INTRED(x)    (int(x))
#define _INTGREEN(x)  ((int(x))<<8)
#define _INTBLUE(x)   ((int(x))<<16)

// unsigned short to int and reverse Macro

#define _SHORTLINT(x)    (ushort(x & 0x0000ffff))
#define _SHORTHINT(x)    (ushort((x & 0xffff0000) >> 16 ))

#define _INTLSHORT(x)     (uint(x))
#define _INTHSHORT(x)     ((uint(x)) << 16)

const std::string Base16{ "0123456789abcdef" };

//////////////////////////////////// FUNCTIONS ////////////////////////////////////////////////////

namespace Bit {

	constexpr std::pair<ushort, ushort> uint2u2short(uint n) {

		return std::make_pair(_SHORTLINT(n), _SHORTHINT(n));

	}

	constexpr uint u2short2uint(ushort s1, ushort s2) {

		return _INTLSHORT(s1) | _INTHSHORT(s2);

	}

	template<typename Trgb>
	constexpr int rgb2int(const Trgb& color) {
		return  _INTGREEN(color.green) | _INTBLUE(color.blue) | _INTRED(color.red);
	}

	template<typename Trgb>
	constexpr Trgb int2rgb(int n) {      // r g b

		return Trgb{ .red = _RED(n),.green = _GREEN(n), .blue = _BLUE(n) };
	}

	///////////////////////////////// to hexadecimal convertion /////////////////////////////////////////

	std::string char_to_Hex(char c) {

		return "0x" + std::string{Base16[(c & 0xf0) >> 4]} + std::string{Base16[c & 0x0f]};

	}

	std::string short_t_oHex(short s) {

		return "0x" + std::string{Base16[(s & 0xf000)>>12]} + std::string{ Base16[(s & 0x0f00) >> 8] } 
		            + std::string{ Base16[(s & 0x00f0) >> 4] } + std::string{ Base16[s & 0x000f] };

	}

	
}