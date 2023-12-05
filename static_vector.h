/*
    1. This utility just test from STL library
	2. All right reserved to Author: KADDA AOUES
	3. Date : 12 / 12 / 2023




*/


#pragma once
#include <vector>

#define    SV_EXCIDE_CAPACITY_CONDITION(capacity, ret)     if (this->size() == capacity) {     \
                                                   std::cout << "excide the capacity\n";  \
                                                      return ret;                             \
		                                                                            }     \

#define   SV_DISPLAY(comment)               print_ << comment << end_

template<typename T, size_t CAPACITY>
class static_vector : public std::vector<T> {

//	void push_back(const T&);
	void reserve(const size_t);
	void resize(const size_t);
	void resize(const size_t, const T&);
	//void push_back(...);
	void emplace_back(...);
	void emplace(...);
	void insert(...);
	void shrink_to_fit();


public:

	static_vector() {
		std::vector<T>::reserve(CAPACITY);
	}

	static_vector(size_t Size, const T& val)
	{
		std::vector<T>::reserve(CAPACITY);
		if (Size > CAPACITY) Size = CAPACITY;
		
		std::vector<T>::resize(Size, val);
	}

	static_vector(size_t Size) : static_vector(Size,T{}){}

	static_vector(std::initializer_list<T> init) 
	{
		std::vector<T>::reserve(CAPACITY);

		for (auto element : init) {
			this->push_back(element);
		}
	}

	~static_vector() {};


	void push_back(const T& val) {
		SV_EXCIDE_CAPACITY_CONDITION(CAPACITY)
		std::vector<T>::push_back(val);
	}

	void push_back(T&& val) {
		SV_EXCIDE_CAPACITY_CONDITION(CAPACITY)
		std::vector<T>::push_back(val);
	}

	/*
	    iterator insert( iterator pos, const T& value );                        (until C++11)
        iterator insert( const_iterator pos, const T& value );                  (since C++11)
        iterator insert( const_iterator pos, T&& value );        (3) (2)        (since C++11)
        void insert( iterator pos, size_type count, const T& value );           (until C++11)
        iterator insert( const_iterator pos, size_type count, const T& value ); (since C++11)
        (4)	
        template< class InputIt >
        void insert( iterator pos, InputIt first, InputIt last);                (until C++11)

        template< class InputIt >
        iterator insert( const_iterator pos, InputIt first, InputIt last );     (since C++11)

        iterator insert( const_iterator pos, std::initializer_list<T> ilist );

	*/

	std::vector<T>::iterator insert(std::vector<T>::iterator _Where, const T& value) {
		SV_EXCIDE_CAPACITY_CONDITION(CAPACITY, this->end())
		return std::vector<T>::insert(_Where, value);
	}

	std::vector<T>::iterator insert(std::vector<T>::const_iterator _Where, const T& value) {
		SV_DISPLAY("call function insert(const_it, const T&)");
		SV_EXCIDE_CAPACITY_CONDITION(CAPACITY, this->end())
			return std::vector<T>::insert(_Where, value);
	}

	//std::vector<T>::iterator insert(std::vector<T>::const_iterator _Where, T&& value) {
	//	SV_DISPLAY("call functin insert(const_it,T&&)");
	//	SV_EXCIDE_CAPACITY_CONDITION(CAPACITY, this->end())

	//		return std::vector<T>::insert(_Where, value);
	//}

	template<class InputIt>
	void insert(std::vector<T>::iterator _Where, InputIt _first, InputIt _last) {
		SV_DISPLAY("call function insert(it,inIt first, inIt last");
		SV_EXCIDE_CAPACITY_CONDITION(CAPACITY)

			// first we should calculate how much elements need to add:
			size_t diff = _last - _first;
		if (diff + this->size() < CAPACITY + 1)
		std::vector<T>::insert(_Where, _first, _last );
		else
		{
			diff = CAPACITY - this->size();
			std::vector<T>::insert(_Where, _first, _first + diff);
		}
	}

	// for const iterator
	template<class InputIt>
	void insert(std::vector<T>::const_iterator _Where, InputIt _first, InputIt _last) {
		SV_EXCIDE_CAPACITY_CONDITION(CAPACITY)

			// first we should calculate how much elements need to add:
			size_t diff = _last - _first;
		if (diff + this->size() < CAPACITY + 1)
		std::vector<T>::insert(_Where, _first, _last );
		else
		{
			diff = CAPACITY - this->size();
			std::vector<T>::insert(_Where, _first, _first + diff);
		}
	}


};
