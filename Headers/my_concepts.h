#pragma once
#include <type_traits>
#include <concepts>

// some metaprogramming 

namespace my_concept {

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    Meta programming concepts 
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	// 1. ARE SAME ALL ARGUMENT TYPES SAME
	template<typename T, typename...Ts>
	constexpr inline bool are_same_v = std::conjunction_v<std::is_same<T, Ts>...>;

	// 2. FIRST ARGUMENT IN TYPES LIST
	template<typename T, typename ...>
	struct first_arg {
		using type = T;
	};

	template<typename...Args>
	using first_arg_t = typename first_arg<Args...>::type;


	// 3. GET A RETURN TYPE OF FUNCTION TEMPLATE OR FUNCTION
	template<typename T>
	struct returnType;

	template<typename R, typename ...Ts>
	struct returnType<R(Ts...)> { using type = R; };

	template<typename T>
	using returnType_t = typename returnType<T>::type;

	// 4. RETURN LIST OF TYPE OF FUNCTION
	template<typename...Ts>
	struct list_types;

	template<typename  Function>
	struct function_arguments;

	template<typename R, typename ...Args>
	struct function_arguments<R(Args...)> {
		using type = list_types<Args...>;
	};

	template<typename T>
	using function_arguments_list = typename function_arguments<T>::type;


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    CONCEPTS 
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	// NEGATIVE AND POSITIVE
	template<typename T, T x>
	concept Negative = x < static_cast<T>(0);

	template<typename T, T y>
	concept Positive = y > static_cast<T>(0);

	// concepte of post increment 
	template<typename T>
	concept Pre_Incrementable = requires(T r) { ++r; };

	template<typename T>
	concept Post_Incrementable = requires(T r) { r++; };

	template<typename T>
	concept Pre_Decrementable = requires(T r) { --r; };

	template<typename T>
	concept Post_Decrementable = requires(T r) { r--; };

	// concept of size of
	template<typename T, size_t N>
	concept SizeOf = (sizeof(T) == N);



	// concepts Addable
	template<typename...Args>
	concept Addable = requires(Args...args)
	{
		(... + args);
			requires are_same_v<Args...>;
			requires sizeof...(Args) > 1;
		{(... + args)} noexcept -> std::same_as<first_arg_t<Args...>>;
	};


#define REQUERES(_Class, _Type ,_Function)  requires(_Class C,_Type value){ C._Function(value);}

#define MAKE_HAS_FUNCTION(_Class, _Type, _Function) template<typename _Class, typename _Type> \
          concept  Has_##_Function = REQUERES(_Class, _Type, _Function)                       \


	template< typename Container, typename T>
	concept HasPushBack = requires (Container t, T value) {

		t.push_back(value);
	};

	template<typename Container>
	concept HasPushBack2 = requires(Container C, typename Container::value_type value) {
		C.push_back(value);
	};

	template<typename Container>
	concept HasPushBack3 = requires(Container C) {
		C.push_back(std::declval<typename Container::value_type&>());
	};

}

namespace Concept = my_concept;