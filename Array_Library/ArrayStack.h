#pragma once
#include <iostream>
#include "ArrayUtility.h"


/*                             ABSTRACT STACK CLASS                           */

template<typename T>
class _Stack {
	//int capacity;
	//int stackSize;
	//T* a;
public:
	virtual ~_Stack() {}
	virtual void push(const T&) = 0;
	virtual T   pop()    = 0;
	virtual bool empty() const  = 0;
	virtual int  size()  const  = 0;
	virtual T& top() const = 0;
};

template<typename T>
class ArrayStack :public _Stack<T>
{
protected:
	int capacity;
	int stackSize;
	T* a;

public:
	ArrayStack(const int _capacity = 10)
		:capacity{_capacity},stackSize{}
	{
		if (_capacity < 10) { std::cout << "Error\n"; capacity = 10; }

		a = new T[capacity];
	}

	ArrayStack(const ArrayStack<T>& stack) {
		capacity = stack.capacity;
		stackSize = stack.stackSize;
		a = new T[capacity];
		std::copy(stack.a, stack.a + capacity, a);
	}

	~ArrayStack() { delete[] a; }

	void push(const T& x) {
		// test capacity
		if (stackSize == capacity)
		{
			arrayResize<T>(a, capacity, 2 * capacity);
			capacity *= 2;
            std::copy_backward(a, a + stackSize, a + capacity);
		}
		stackSize++;
		a[capacity - stackSize] = x;
	}

	T pop() {
		if (stackSize == 0) { std::cout << "empty stack\n"; return T{}; }
		T temp = a[capacity - stackSize];
		stackSize--;
		a[capacity - stackSize + 1].~T();
		return temp;
	}

	T& top() const {
		return a[capacity - stackSize];
	}

	bool empty() const { return stackSize == 0; }

	int size() const { return stackSize; }

	void output() const {

		for (int i = 0; i < stackSize; i++)
			std::cout << a[capacity + i - stackSize ] << " ";
		std::cout << '\n';
		std::cout << "capacity " << capacity << " Size " << stackSize << '\n';
	}

};

