#pragma once
#include <vector>
#include <sstream>
#include "C:\Users\Acer\source\MyLib\stringfunctionhelper.h"

//int operator [] (int n) {                                      // get a bit at n from the right
//	int x = (i & (1 << n)) >> n;
//	return std::abs(x);
//}
// C:\Users\Acer\source\Course C++\BitWise\Template__Exemple1

namespace Bit {

	enum Bit { Zero = 0, One };

	std::ostream& operator << (std::ostream& os, std::vector<short> v_bit) {

		for (int i = 0; i < v_bit.size(); i++)
		{
			os << "[ " << i << " , " << v_bit[i] << " ] ";
			if (i % 12 == 11) std::cout << '\n';
		}

		return os;
	}

	template<typename T>
	std::vector<Byte> byte_of_c(T x) {

		std::vector<Byte> vbyte;
		int sz = sizeof(T);
		Byte* pByte;
		pByte = (Byte*)&x;
		for (int i = 0; i < sz; i++) vbyte.push_back(*(pByte + i));
		return vbyte;
	}

	template<typename T>
	std::vector<short> bit_of_c(T x) {

		std::vector<short> vbit;

		Byte* pbyte = (Byte*)&x;

		for (int i = 0; i < sizeof(T); i++)
			for (int j = 0; j < 8; j++)
				vbit.push_back(short(((*(pbyte + i)) & (1 << j)) >> j));

		return vbit;
	}

	// Transfer all bit to output string ------------------------------------------
	template<typename T>
	std::string string_bit_of(T x) {

		Byte* pbyte = (Byte*)&x;
		std::stringstream sstr;
		std::string str;

		for (int i = 0; i < sizeof(T); i++)
			for (int j = 0; j < 8; j++)
				sstr << ((*(pbyte + i) & (1 << j)) >> j);
		str = Str::reverseString(sstr.str());

		return Str::remove_unusefullZero(str);
	}

	// get a bit at position 'n'

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    C function for get bit at position
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    C use Union methode to get bit at position
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T, int N = sizeof(T)>  // use union 
	T set_bit_at_(T x, int n) {
		if (n < 0 || n > N) { std::cout << "number of bit is out of size of type\n"; return T{}; }

		byte_type<T> byte_t;
		byte_t.type = x;
		int _n = n / 8;
		int __n = n % 8;
		byte_t.byte[_n] = byte_t.byte[_n] | (1 << __n);

		x = byte_t.type;
		return x;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    C++ optimized and safe methode to get bit at position
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////



	template<typename T>   // use pointer
	T off_bit_at(T x, int n) {
		if (n < 0 || n > 8 * sizeof(T)) { std::cout << "number of bit is out of size of type\n"; return T{}; }

		Byte* pbyte = (Byte*)&x;
		int _n = n / 8;
		int __n = n % 8;

		*(pbyte + _n) = ~(~(*(pbyte + _n)) | (1 << __n));

		return x;
	}

	// set bit value at position ............
	template<typename T>
	T set_bit_value_at(T x, Bit value, int n) {

		if (n < 0 || n > 8 * sizeof(T)) { std::cout << "number of bit is out of size of type\n"; return T{}; }
		Byte* pbyte = (Byte*)&x;
		int _n = n / 8;
		int __n = n % 8;

		if (value == Bit::One)
			*(pbyte + _n) = *(pbyte + _n) | (1 << __n);
		else
			*(pbyte + _n) = ~(~(*(pbyte + _n)) | (1 << __n));

		return x;
	}

	// set entire value of byte (unsigned char) to data type in position relative n
	template<typename T, int N = sizeof(T)>
	T set_byte_value_at(T x, Byte byte, int n) {

		if (n > N - 1) { std::cout << "out of range of data\n"; return T{}; }

		Byte* pByte = (Byte*)&x;
		*(pByte + n) = byte;
		return x;
	}



	// make a all possible narrowing of big data to small data type;
	// primary template for upsized type;
	// we don't care about what type mean or what data cary on
	template<typename S, typename T, int sz_S = sizeof(S), int sz_T = sizeof(T)>
	std::vector<S> map_type_to_vector(T x) {

		std::vector<S> v_S_value;
		S _x{};
		int diff_sz = sz_T - sz_S;

		if (diff_sz < 0) diff_sz = 0;

		Byte* pbyte_T = (Byte*)&x;
		Byte* pbyte_S = (Byte*)&_x;

		for (int i = 0; i < sz_T - sz_S + 1; i++)
		{
			for (int j = 0; j < sz_S; j++)
			{
				*(pbyte_S + j) = *(pbyte_T + j + i);
			}
			v_S_value.push_back(_x);
		}
		return v_S_value;
	}

	// helper function for printing 
	//template<typename T>
	//void print_v(std::vector<T> v) {

	//	for (int i = 0; i < v.size(); i++)
	//		std::cout << v[i] << " , ";
	//	std::cout << std::endl;
	//}

	// Check if vector of bit is really vector of bit
	// type trait that should be T is algebraic type.
	template<typename T>
	constexpr bool is_vector_bits(const std::vector<T>& vbit)
	{
		for (auto& bit : vbit)
		{
			if (bit != 1 && bit != 0) return false;
		}

		return true;
	}

	constexpr int make_2short_int(short lo, short hi)
	{
		int x{};
		short* p = (short*)&x;
		*p = lo;
		*(p + 1) = hi;
		return x;
	}

	

	//template<typename T>
	//constexpr std::vector<short> split_type_to_nbit(T x, short n) {
	//	static_assert(n < 9 && n > -1);
	//
	//
	//}

	/*
		 Create New function that copy a byte from type T to type U

	*/
	template<typename T, typename U>
	constexpr U Tcopy(const T& source, U& distination) { // will add also number of bit should be copied
		static_assert(std::is_pod<T>::value && std::is_pod<U>::value, "two type should be old plain data");
		static_assert(!std::is_pointer<T>::value && !std::is_pointer<U>::value, "no pointer in these function");
		static_assert(sizeof(U) >= sizeof(T), "size of distination less than source");
		// should be old data type
		Byte* p_source = (Byte*)&source;
		Byte* p_distination = (Byte*)&distination;

		for (int i = 0; i < sizeof(T); i++)
		{
			*(p_distination + i) = *(p_source + i);
		}
		return distination;
	}

	//
	//template<typename T,typename ...U> 
	//void Tcopy(T& distination, const U& ...arg) {
	//
	//}



	// bit iterator is next project 
	template<typename iter>
	void /* void* */ bititerator() {  // iterate on bit of data
		return;
	}

}