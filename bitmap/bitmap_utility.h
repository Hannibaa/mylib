#pragma once
#include "MyLib\bitmap\bitmap_image.hpp"


#define end_ '\n'
#define Line cout << "---------------------------------------------------------------------\n"
#define print std::cout 

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

////////////////////// STRUCTURE MAY NEED IT RGB //////////////////////////////////////////////////////

struct _rgb {
	union {
		struct {
			unsigned char red;
			unsigned char green;
			unsigned char blue;
		};
		struct {
			unsigned char r;
			unsigned char g;
			unsigned char b;
		};
	};

	_rgb() = default;
	_rgb(uchar _r, uchar _g, uchar _b) : r{ _r }, g{ _g }, b{ _b } {}
	_rgb(bitmap_image::rgb_t rgb) : r{ rgb.red }, g{ rgb.green }, b{ rgb.blue } {}

	bitmap_image::rgb_t as() {
		bitmap_image::rgb_t rgb_t;
		rgb_t.blue = b;
		rgb_t.green = g;
		rgb_t.red = r;
		return rgb_t;
	}
};

/*///////////////////// GET A WIDTH AND HEIGHT OF IMAGE FROM LENGTH OF ARRAY RGB ////////////////////*/

std::pair<int, int> get_width_height(int length) {

	int width{};
	int height{};

	int l = (int)std::sqrtf(float(length));
	print << "first width - height " << l << end_;

	for (int i = 0; i < l; i++) {
		if (length % (l - i) == 0)
		{
			height = l - i;
			width = length / height;
			break;
		}
	}

	// if there are to big diference between width and hieght
	if (width > 2 * height) {
		width = l;
		height = l;
	}

	return std::pair{ width,height };
}

/////////////////////////// FUNCTION INT TO RGB AND RGB TO INT ////////////////////////////////////////

int rgb_to_int(const rgb_t& rgb) {

	union int_rgb {
		int i;
		rgb_t _rgb;
	};

	int_rgb Intrgb{};
	Intrgb._rgb = rgb;

	return Intrgb.i;
}

template<typename RGB>
int rgb_to_int1(const RGB& rgb) {   // should be have 3 byte field structure 
	int i = *(int*)&rgb;
	i = i >> 8;
	i = i & 0x00ffffff;
	return i;
}


constexpr int rgb2int(const rgb_t& color) {
	return  _INTGREEN(color.green) | _INTBLUE(color.blue) | _INTRED(color.red) ;
}


constexpr rgb_t int2rgb(int n) {      // r g b

	return rgb_t{.red = _RED(n),.green = _GREEN(n), .blue = _BLUE(n)};
}

rgb_t int_to_rgb(int n) {

	union int_rgb {
		int i;
		rgb_t _rgb;
	};

	int_rgb Intrgb{};
	Intrgb.i = n;

	return Intrgb._rgb;

}

constexpr std::pair<ushort, ushort> uint2u2short(uint n) {

	return std::make_pair(_SHORTLINT(n), _SHORTHINT(n));
}

constexpr uint u2short2uint(ushort s1, ushort s2) {

	return _INTLSHORT(s1) | _INTHSHORT(s2);
}