#pragma once
#include <MyLib/containers.h>




template<class SET, typename KeyGenerator >
void make_random_set1(SET& Set, KeyGenerator key_gen, size_t Size) {

	while (Size--) {
		typename SET::value_type key = key_gen();
		Set.insert(key);
	}
}



template<class MAP, typename Key_Random_Generator, typename Type_Random_Generator>
void make_random_map1(MAP& map, 
                     Key_Random_Generator key_gen,
	                 Type_Random_Generator type_gen,
	                 size_t Size)
{
	// Key should be integer value; Key_Generator()->Key;
    // T should be integer or string value; Type_generator()->T;

	while (Size--) {

		typename MAP::key_type   key = key_gen();
		typename MAP::mapped_type value = type_gen();
		map[key] = value;

	}
}



    //////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//     INCREMENT FUNCTIONS AND FUNCTIONS OBJECT AND LAMBDAS.
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

// increment object function
auto inc_int = []() {static size_t i{}; return i++; };
auto int_inc = []<size_t N>() { static size_t i{}; return i++; };

template<size_t N>
class Inc_Int {
public:
	size_t operator()() {
		static size_t i{};
		return i++;
	}
};

template<typename T, size_t N>
	requires requires(T z) { z++; }
T inc_function() {
	// or should be equiped with ()++ operator.
	static T i{};
	return i++;
}

decltype(inc_int) inc_int2;
