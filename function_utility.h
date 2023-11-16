#pragma once


/*
* AOUES KADDA PROJECT LIBRARIES :
* 
      FUNCTION UTILITY LIBRARY 
      1. MATHEMATICAL FUNCTIONS
      2. HAND MADE FUNCTION 
      3. NUMURICAL FUNCTION
      4. ALGEBRIAC FUNCTION

*/

#include <MyLib/Console_Library/escape_code.h>



namespace Function {

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//     1. Type comparing functions
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T1, typename T2>
	constexpr bool greaterSize(const T1& o1, const T2& o2) noexcept {
		return sizeof(T1) > sizeof(T2);
	}

	template<typename T1, typename T2>
	constexpr bool equalSize(const T1& o1, const T2& o2) noexcept {
		return sizeof(T1) == sizeof(T2);
	}

	template<typename T1, typename T2>
	constexpr bool lessSize(const T1& o1, const T2& o2) noexcept {
		return sizeof(T1) < sizeof(T2);
	}

	template<typename T>
	constexpr size_t SizeOf(const T& obj) noexcept {
		return sizeof(obj);
	}

	template<typename T1, typename T2, typename MesureFunction >
	constexpr bool compareSize(const T1& o1, const T2& o2, MesureFunction mesure) noexcept {
		return mesure(o1,o2);
	}

	template<typename T>
	constexpr size_t SizeOf() noexcept {
		return sizeof(T);
	}

	template<typename T>
	struct Size_Of
	{
		enum { size = sizeof(T) };

		constexpr size_t operator () (void) noexcept { return sizeof(T); }
	};

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//      Indicator Function : element that can contain in any container
	//      return 1 if is there, else 0;
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T, typename Container>
	requires std::is_same_v<T,typename Container::value_type>
	constexpr bool Indicator(const T& x, const Container& container) {
		return true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//      Algebraic Functions About Maximum-Minimum  built-in type.
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////


	template<typename T>
	constexpr T max_of = T{};

	template<typename T>
	constexpr T min_of = T{};

	template<> constexpr  int max_of<int> = INT_MAX;
	template<> constexpr  int min_of<int> = INT_MIN ;
	template<> constexpr  int max_of<short> = SHRT_MAX;
	template<> constexpr  int min_of<short> = SHRT_MIN;
	template<> constexpr  int max_of<char> = CHAR_MAX;
	template<> constexpr  int min_of<char> = CHAR_MIN;
	template<> constexpr  long int      min_of<long int> =	LONG_MIN	;
	template<> constexpr  long int      max_of<long int> =	LONG_MAX	;
	template<> constexpr  long long     max_of<long long> =	LLONG_MAX	;
	template<> constexpr  long long     min_of<long long> =	LLONG_MIN	;
	template<> constexpr  int max_of<unsigned short> = USHRT_MAX;
	template<> constexpr  int max_of<unsigned char> = UCHAR_MAX;
	template<> constexpr  unsigned int  max_of<unsigned int > =	UINT_MAX	;
	template<> constexpr  unsigned long max_of<unsigned long> =	ULONG_MAX	;
	template<> constexpr  unsigned long long max_of<unsigned long long> =	ULLONG_MAX  ;

	template<typename T>
	constexpr T max_v() { if (max_of<T> == T{}) std::cout << "not built-in type\n"; return max_of<T>; }

	template<typename T>
	constexpr T min_v() { if (min_of<T> == T{}) std::cout << "not built-in type\n"; return min_of<T>; }

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//      FACTORIAL FUNCTION IN RUN AND COMPILE TIME
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////


	// 1. Run time Factorial function 
	template<typename T>
	requires std::is_integral_v<T>
	constexpr T factorial(const T& n) {
		if (n == static_cast<T>(1) or n == static_cast<T>(0) ) return static_cast<T>(1);

		return n * factorial(n - 1);
	}

	// 2. Compile Time Factorial function
	template<size_t n>
	struct Factorial {
		static const size_t value = n * Factorial<n - 1>::value;
	};

	template<>
	struct Factorial< 0 > {
		static const size_t value = 1;
	};

	template<size_t n>
	size_t factorial_v = Factorial<n>::value;

	// 3. power of 2 :

	template<int N, typename T>
	constexpr T _power2 = static_cast<T>(1ull << 1);

	// 4. factorial function 
	
	template<typename T>
	constexpr T Fact_Func(T f(T), T N) {  // WE ALWAYS USE F = 0;
		static_assert(std::is_integral_v<T>, "T should be integral type");
		T M = 1;
		for (T i = 0; i < N; i++)
		{
			M = f(i + 1) * M;
		}
		return M;
	}

	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    Floating Point : 1. Increment and decrement 
	//                     2. ...
	//                     3. 
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	// Increment of floating 

	float float_inc(float f, int inc = 1)  {

		*(int*)&f += f > 0 ? inc : -inc;

		return f;
	}

	template<typename Double>
	requires std::is_floating_point_v<Double> && (sizeof(Double) == 8)
	double float_inc(double f, int64_t inc = 1) 
	{

		*(int64_t*)&f += f > 0 ? inc : -inc;

		return f;

	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//      CONVERSION BETWEEN TRIVIALLY COPYABLE TYPE 
	//      USING UNION 
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T1, typename T2>
	union Xunion {
		T1 value1;
		T2 value2;

		Xunion(T1 t1) : value1{ t1 } {}
		Xunion(T2 t2) : value2{ t2 } {}
	};

	template<typename To_, typename From_>
		requires (sizeof(To_) == sizeof(From_)) && std::conjunction_v<std::is_trivially_copyable<To_>,
	                                                                  std::is_trivially_copyable<From_>>
		                                        && (!std::is_pointer_v<To_>)
		                                        && (!std::is_pointer_v<From_>)
		To_ to_(From_ from) {
		//Xunion<To_, From_> x{ from };
		return Xunion<To_, From_>{from}.value1;
	}

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //     CLAMP FUNCTIONS THAT WE NEED  
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

     template<typename T>
     constexpr T clamp(const T& v, const T& lo, const T& hi)
     {
      return v < lo ? lo : hi < v ? hi : v;
     }

	 template<auto lo_value, auto hi_value>
	 requires std::same_as<decltype(lo_value),decltype(hi_value)> && 
	          std::is_arithmetic_v<decltype(lo_value)>  
	 constexpr auto clamp(decltype(lo_value) value) {
		 return value < lo_value ? lo_value : hi_value < value ? hi_value : value;
	 }
     

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//      Union ???
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T1, typename T2>
	union ptr_2type {
	  T1* ptr1;
	  T2* ptr2;
	};

}

namespace Fn = Function;