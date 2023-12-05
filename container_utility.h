/*
 *****************************************************************************
 *                                                                           *
 *                          Platform Independent                             *
 *                ****************************************                   *
 *                * Container utility functions  Library *                   *
 *                ****************************************                   *
 *                                                                           *
 * Author: KADDA Aoues - haoues_k@yahoo.fr - 2023                            *
 *                                                                           *
 * URL :                                                                     *
 *                                                                           *
 * Copyright notice:                                                         *
 * Free use of the Library CFile                                             *
 * is permitted under the guidelines and in accordance with the most current *
 * version of the MIT License.                                               *
 * http://www.opensource.org/licenses/MIT                                    *
 *                                                                           *
 *****************************************************************************
*/


#pragma once
#include <concepts>
#include <string_view>

#ifndef print_
#define print_       std::cout 
#endif // !print_

#ifndef end_
#define end_         '\n'
#endif // !end_

#ifndef BACKSPACE
#define BACKSPACE      '\b'
#endif // !BACKSPACE







namespace Container {

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    Concept :
	//       1. true only if a type have sub type : key_type and mapped_type.
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename Container>
	concept Has_Mapped_and_Key_Type = requires{
		typename Container::key_type;
		typename Container::mapped_type;
	};


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //    ROTATE THE VALUE OF A VECTOR OR AN ARRAY ,C-TYPE ARRAY AND GET NEW VALUE
    //    SHIFT RIGHT AND LEFT AND GET NEW VALUE .
    //    1.Parameter : 
    //       valueU, valueV : new values assigned to first element of _U and _V
    //       _U, _V         : is C type arrays 
    //       array_size     : size of _U, _V.
    //    2. Return :
    //       void
    // 
    // 	   int d[] = { (cout << args << " ",0)... };
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<size_t array_size, typename T>
	void rotate_array_to_value(T value, T* _V) {
		for (size_t k = array_size - 1; k != 0; --k)
		{
			_V[k] = _V[k - 1];
		}

		_V[0] = value;
	}

	// TODO  fixing this problem of deduction parameter
	//template<size_t array_size, typename ...Ts >
	//void rotate_array_value(Ts...vs, Ts* ... _Vs) {

	//	(retate_array_to_value<array_size, Ts>(vs, _Vs), ...);

	//}

	template<typename Container>
		requires requires {
		typename Container::value_type;
			requires !Has_Mapped_and_Key_Type<Container>;
	}
	void rotate_container_to_value(const typename Container::value_type& value, Container& container)
	{
		for (size_t k = container.size() - 1; k != 0; --k)
		{
			container[k] = container[k - 1];
		}

		container[0] = value;
	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    FOR A GIVEN VALUE, GET UPPER AND LOWER BOUND OF THIS VALUE 
	//    1.Parameter
	//      1.1 Container that have compare function.
	//      1.2 key is of the type key::type
	//    2.Return
	//      std::pair<Container::iterator, Container::iterator>
	//      first point to upper value and second to lower, due 
	//      to compare function of Container
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename Container, typename It = typename Container::iterator>
		requires requires { typename Container::key_compare;
	                        typename Container::key_type; }
	std::pair<It, It>  get_Interval(Container& set, const typename Container::key_type& key) {

		if (set.contains(key)) return std::pair(--set.upper_bound(key), --set.upper_bound(key));

		if (set.upper_bound(key) == set.begin()) return std::pair(set.begin(), set.begin());
		if (set.upper_bound(key) == set.end()) return std::pair(--set.end(), --set.end());

		It it1 = set.upper_bound(key);
		It it2 = --set.upper_bound(key);

		return std::pair(it2, it1);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    Adaptor for container : in value not inside of the container it will select one of closet 
	//                            value to it.
	//    have operator[] only . and selector function 
	//    + this easiest implimentation of selector function.
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename Container>
		requires requires {
		typename Container::key_compare;
		typename Container::key_type;
		typename Container::mapped_type;
	}
	class InterContainer {

		Container* ptr_container;

		using mapped_type = typename Container::mapped_type;
		using key_type = typename Container::key_type;
		using key_compare = typename Container::key_compare;
		using Iterator = typename Container::iterator;

		mapped_type inter_func(const key_type& key) {
			if (ptr_container->contains(key)) return ptr_container->at(key);
			auto it = ptr_container->upper_bound(key);
			if (it == ptr_container->end()) return (--ptr_container->end())->second;
			return it->second;
		}

		// todo : implement function to get closest value. closest_value(container,value);
		mapped_type inter_func_2(const key_type& key) {
			auto p = get_Interval(*ptr_container, key);

			return{};
		}

	public:
		InterContainer(Container* _ptr)
			: ptr_container{ _ptr }
		{}

		~InterContainer() { ptr_container = nullptr; }

		mapped_type operator[](const key_type& key) {
			return inter_func(key);
		}
	};


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    PRINTING FUNCTION FOR CONTAINER
	//    1. Parameter :
	//       1.1 container : any standard containers
	//       1.2 comment   : string comment add on beginning of printing
	//    
	//    2. Concept : for container that have key and mapped value.
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////


	template<typename Container>
	void print_container(const Container& container, std::string_view comment = "") {

		if (container.empty()) {
			Print_(color::Red, "There no element :") << COLOR(color::Yellow, "[Empty Container]") << end_;
			return;
		}

		print_ << comment << end_;
		for (const auto& element : container)
			if constexpr (Has_Mapped_and_Key_Type<Container>)
				print_ << "{" << element.first << " , " << element.second << "} ,";
			else
				print_ << element << " , ";

		print_ << BACKSPACE << BACKSPACE << ' ' << end_;
	}



}

namespace cu = Container;