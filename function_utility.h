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

		constexpr std::size_t operator () (void) noexcept { return sizeof(T); }
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
	//      Algebraic Functions
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////


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

	// 3. power of 2 :

	template<int N, typename T>
	constexpr T _power2 = static_cast<T>(1ull << 1);

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


}