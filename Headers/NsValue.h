#pragma once
#include <MyLib/random_generator.h>
#include <MyLib/my_metaprog.h>

/*
          THIS CLASS OF ARRAY OF NUMBER WILL STORE ARRAY OF SIZE N,
		  AND EQUIPED BY CONVERSION OPERATOR THAT RETURN A RANDOM VALUE FROM THIS ARRAY

		  TODO : 
		  1. constructors and more vectors and array extend to any class type .
*/


template<typename T, size_t N>
class NsValue {
	static_assert(std::is_trivially_copyable_v<T>, "T type should be copyable");
	T x[N]{};

public:

	NsValue() : x{} {}
	NsValue(const T(&a)[N])  {
		puts("NsValue(const T(&a)[N])");
		std::memcpy(x, a,sizeof(T) * N);
	}

	template<typename ...Ts>
	NsValue(Ts...ts) : x{ T(ts)... } {
		static_assert(N <= sizeof...(Ts), "number of argument should be equal to size of N");
		//T x1 = {T(ts)...};
		puts("NsValue(Ts...ts)");
	}

	operator T () {

		RNG::RG<int> random(0, N - 1);
		return x[random()];
	}

	T* get_ref() { return x; }
};

template<typename T, size_t N>
NsValue(const T(&)[N]) -> NsValue<T, N>;

template<typename...Ts>
NsValue(Ts...) -> NsValue<typename meta::first_type<Ts...>::type, sizeof...(Ts)>;

template<typename T, size_t N>
void print_value(NsValue<T, N>& ns_value) {

	auto ptr = ns_value.get_ref();

	for (int i = 0; i != N; ++i) {
		std::cout << *(ptr + i) << " ";
		if ((i + 1) % 35 == 0) std::cout << '\n';
	}
}