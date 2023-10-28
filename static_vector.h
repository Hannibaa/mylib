#pragma once
#include <vector>


template<typename T, size_t CAPACITY>
class static_vector : public std::vector<T> {

//	void push_back(const T&);
	void reserve(const size_t);
	void resize(const size_t);
	void resize(const size_t, const T&);

public:

	static_vector() {
		std::vector<T>::reserve(CAPACITY);
	}

	static_vector(size_t Size, const T& val )
	{
		std::vector<T>::reserve(CAPACITY);
		if (Size > CAPACITY) Size = CAPACITY;
		
		std::vector<T>::resize(Size, val);
	}

	static_vector(size_t Size) : static_vector(Size,T{}){}

	using std::vector<T>::vector;

	void push_back(const T& val) {
		std::cout << "push back call\n";
		if (this->size() == CAPACITY) {
			std::cout << "excide the capacity\n";
			return;
		}
		std::vector<T>::push_back(val);
	}

	template<typename...Ts>
	decltype(auto) emplace_pack(Ts&&... vals){}
};