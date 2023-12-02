#pragma once
#include <vector>
#include <array>
#include <list>
#include <forward_list>
#include "MyLib\random_generator.h"

namespace Vector_Utility {

	template<typename T, template<typename...> class Container = std::vector>
	T get_random_element(Container<T>& container) {

		if (container.size() == 0) return {};

		RNG::RG<int> index(0, container.size() - 1);

		return container[index()];
	}

	template<typename T>
	T get_random_element(T* array, size_t arraySize)
	{
		if (arraySize == 0) return T{};
		if (array == nullptr) return {};

		RNG::RG<size_t> index{ 0, arraySize - 1 };

		return array[index()];

	}

	template<typename iter>
	typename iter::value_type get_random_element(iter first, size_t numberOfelement) {

		RNG::RG<size_t> index{ 0, numberOfelement };

		size_t _index = index();

		return *(first + _index);

	}

	template<typename iter>
	typename iter::value_type get_random_element(iter first, iter last) {

		size_t numberOfelement = std::distance(first, last);

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<std::size_t> index{ 0, numberOfelement - 1 };

		numberOfelement = index(gen);

		while (--numberOfelement) ++first;

		return *first;
	}

	// function that can modifing this and return T& not work?!

	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//   MAKE RANDOM VECTOR OF TYPE T , SIZE N
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	std::vector<T> makeRandomVector(T min, T max, size_t size) {

		static_assert(std::is_arithmetic<T>::value, "T should be arithmetic type");

		RNG::RG<T> random(min, max);

		std::vector<T> Vector;

		for (size_t i = 0; i < size; ++i) Vector.push_back(random());

		return Vector;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//     ANOTHER VERSION OF MAKE A VECTOR
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	

	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//   MAKE RANDOM ARRAY OF TYPE T , SIZE N.
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T, size_t N>
	std::array<T, N> makeRandomArray(T min, T max) {

		static_assert(std::is_arithmetic<T>::value, "T should be arithmetic type");

		RNG::RG<T> random(min, max);

		std::array<T, N> Array;

		for (size_t i = 0; i < N; ++i) Array[i] = random();

		return Array;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//   MAKE RANDOM HEAP ARRAY OF TYPE T , SIZE N.
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	T* makeRandomCarray(T min, T max, size_t N) {

		static_assert(std::is_arithmetic<T>::value, "T should be arithmetic type");

		RNG::RG<T> random(min, max);

		T* Array = new T[N]{};

		for (size_t i = 0; i < N; ++i) Array[i] = random();

		return Array;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//      MAKE RANDOM ARRAY IN STACK, AN ARRAY SHOULD BE DEFINED APRIORY
	//      constexpr unsigned int N;
	//      T array[N]; 
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template< size_t N, typename T>
	void makeRandomStackArray(T* _array, T min, T max) {

		RNG::RG<T> random(min, max);

		for (int i = 0; i != N; ++i) _array[i] = random();

	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//   MAKE RANDOM LIST 
	//    
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	// double linked list *************************************************************************
	template<typename T>
	std::list<T> makeRandomList(T min, T max, size_t size) {
		static_assert(std::is_arithmetic_v<T>, "T sould be arithmetic type");

		RNG::RG<T> random(min, max);

		std::list<T> List;

		for (size_t i = 0; i != size; ++i)
			List.emplace_back(random()); 		return List;
	}
	
	// simple forward linked list *****************************************************************
	template<typename T>
	std::forward_list<T> makeRandomForwardList(T min, T max, size_t size) {
		static_assert(std::is_arithmetic_v<T>, "T sould be arithmetic type");

		RNG::RG<T> random(min, max);

		std::forward_list<T> List;

		for (size_t i = 0; i != size; ++i)
			List.emplace_front(random());
		
		return List;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//       MAKE GENERALIZED MAKE_CONTAINER() -> CONTAINER ;
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename Container, typename T = Container::value_type>
	Container makeRandomContainer_2(T min, T max, size_t N) {

		RNG::RG<T> random(min, max);

		Container container;
		container.resize(N);

		for (auto it = container.begin(); it != container.end(); ++it) {
			*it = random();
		}

		return container;
	}

	template<template<typename,typename...>class Container, typename T>
	Container<T> makeRandomContainer(T min, T max, size_t N) {

		RNG::RG<T> random(min, max);

		Container<T> container;

		container.resize(N);

		for (auto it = container.begin(); it != container.end(); ++it) {
			if constexpr ( std::is_floating_point_v<T> )
			*it = random(1.f);
			else
			*it = random();
		}

		return container;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    make equi - distance container
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename Container, typename T = typename Container::value_type>
	Container make_equi_distance_container(T min, T max, size_t number_values)
	{
		Container v;
		v.insert(v.end(),min);

		T offset = (max - min) / static_cast<T>(number_values - 1);
		
		for (size_t t = 1; t < number_values - 1; ++t) {
			v.insert(v.end(), min + offset * static_cast<T>(t));
		}

		v.insert(v.end(), max);

		return v;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    MAKE CONTAINER BY USING GENERATOR(), MAY RANDOM OR NOT.
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	template<typename Container, typename T, typename Generator>
		requires requires(Container c, T t) { c.push_back(t); }
	Container make_container(size_t numbers, T min, T max, Generator generator) {
		Container container{};
		for (size_t t = 0; t != numbers; ++t) {
			container.push_back(generator(min, max));
		}

		return container;
	}

}

namespace vu = Vector_Utility;