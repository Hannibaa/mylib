#pragma once

// list<T> with operator []

template<typename T>
class List : public std::list<T> {

public:
	using std::list<T>::list;

	T operator [](size_t index) const {
		if (index > (*this).size()) return T{};
		for (auto it = this->begin(); it != this->end(); ++it) if (index-- == 0) return *it;
	}
};

template<typename R, typename ...T>
class List2 : public std::list<R, T...> {

public:
	using std::list<R, T...>::list;

	R operator [](size_t index) const {
		if (index > (*this).size()) return T{};
		for (auto it = this->begin(); it != this->end(); ++it) if (index-- == 0) return *it;
	}

};