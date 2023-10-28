#pragma once
#include <vector>

template<typename T>
class OneElement_vector : public std::vector<T> {

	using std::vector<T>::resize;
	using std::vector<T>::reserve;
	using std::vector<T>::push_back;
	using std::vector<T>::pop_back;
	using std::vector<T>::insert;
	using std::vector<T>::emplace;
	using std::vector<T>::emplace_back;
	using std::vector<T>::shrink_to_fit;
	using std::vector<T>::at;
	using std::vector<T>::operator[];

public:


	OneElement_vector() {

		(*this).reserve(1);
		(*this).resize(1);

	}

	OneElement_vector(T x) :OneElement_vector() { this->at(0) = x; }

	operator T () const { return this->at(0); }
};
