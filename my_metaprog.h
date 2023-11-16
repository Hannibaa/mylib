#pragma once

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //    THIS MY PERSONAL LIBRARY THAT I MADE FOR SOME OF MY PROJECT
    //    1. first_type<Ts...>
    //    2. 
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////



namespace my_metaprogramming {

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //    get first type from pack parameter
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////


    template<typename...Ts>
    struct first_type;

    template<typename T0, typename...Ts>
    struct first_type<T0, Ts...> {
        using type = T0;
    };

	template<typename...Ts>
	using first_type_t = typename first_type<Ts...>::type;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //    Get nth type from type-pack
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<size_t N, typename...Ts>
	struct get_nth_type;

	template<typename...Ts>
	struct get_nth_type<0, Ts...> {
		using type = typename first_type<Ts...>::type;
	};

	template<size_t N, typename T1, typename...Ts>
	struct get_nth_type<N, T1, Ts...> {
		static_assert(N < sizeof...(Ts) + 1, "out of range of parameter pack");
		using type = typename get_nth_type<N - 1, Ts...>::type;
	};

	template<size_t N, typename...Ts>
	using get_nth_type_t = typename get_nth_type<N, Ts...>::type;

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//     Get pack less than one pack parameter    
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename ...Ts>
	struct less_pack;

	template<typename T0, typename...Ts>
	struct less_pack<T0, Ts...> {
		using pack_type = less_pack<Ts...>;
	};

	template<typename ...Ts>
	using less_pack_t = typename less_pack<Ts...>::pack_type;

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


	//////////////////// Size of function ///////////////////////////////////////////////////////

	template<typename T>
	constexpr size_t SizeOf() {
		return sizeof(T);
	}

	template<typename T>
	struct Size_Of
	{
		enum { size = sizeof(T) };
		constexpr size_t operator ()(void) const noexcept { return sizeof(T); }
	};

	//////////////////////////////////////////////////////////////////////////////////////

	template<template<typename...> class list, typename...Ts>
	struct get {
		using type = list<Ts...>;
	};

}

namespace meta = my_metaprogramming;