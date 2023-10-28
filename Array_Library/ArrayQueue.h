#pragma once
#include <iostream>

template<typename T>
class _Queue {

public:
	virtual ~_Queue(){}
	virtual bool empty() const = 0;
	virtual int size() const = 0;
	virtual T& front() const = 0;
	virtual T& back() const = 0;
	virtual void push(const T&) = 0;
	virtual T pop() = 0;
};


template<typename T>
class ArrayQueue :public _Queue<T>
{
protected:
	int Size;
	int queueSize;
	int frontIndex;
	int backIndex;
	// const int Max_Capacity = 10; // maximum initial capacity
	T* a;
public:
	ArrayQueue(const int _capacity = 10)
		:Size{_capacity}, frontIndex{},backIndex{}
	{
		if (Size < 10) Size = 10;
		a = new T[Size];
		queueSize = 0;

	}

	ArrayQueue(const ArrayQueue<T>& queue) {

		Size = queue.Size;
		queueSize = queue.queueSize;
		frontIndex = queue.frontIndex;
		backIndex = queue.backIndex;
		a = new T[Size];
		std::copy(queue.a, queue.a + Size, a);
	}

	bool empty() const {
		return queueSize == 0;
	}

	int size() const {
		return queueSize;
	}

	T& front() const {
		if (queueSize == 0) { std::cout << "empty queue\n"; return a[0]; }
		return a[frontIndex];
	}

	T& back() const {
		if (queueSize == 0) { std::cout << "empty queue\n"; return a[0]; }
		
		return backIndex == 0 ? a[queueSize-1] : a[(backIndex - 1) % Size];// changed ?
	}

	void push(const T& x) {
		
		if ( queueSize == Size )
		{
			// Allocate new array
			T* newQueue = new T[2 * Size];

			// copy elements into new array
			
			if (frontIndex == 0 )                           // no wrap around
				std::copy(a , a  + Size , newQueue);
			else
			{                                        // queue wrap around
				std::copy(a + frontIndex, a + Size, newQueue);
				std::copy(a, a + backIndex , newQueue + Size - frontIndex );
			}

			// switch to newQueue
			frontIndex = 0;
			backIndex = Size ;
			Size *= 2;
			
			delete[] a;
			a = newQueue;
		}

		a[backIndex] = x;
		backIndex = (backIndex + 1) % Size;
		queueSize++;
	}

	T pop() {
		if (queueSize == 0)
		{
			std::cout << "empty queue\n";
			return T{};
		} 

		T temp = a[frontIndex];
		a[frontIndex].~T();

		frontIndex = (frontIndex + 1) % Size;
		queueSize--;

		return temp;
	}

	void output() const {
		if (queueSize == 0) { std::cout << "queue empty\n"; return; }

		for (int i = frontIndex; i < std::max<int>(backIndex,queueSize); i++)
		{
			std::cout << a[i] << " ";
		}
		if (backIndex < frontIndex ) 
			for (int i = 0; i < backIndex; i++)
			{
				std::cout << a[i] << " ";
			}

		std::cout << '\n';
	}

	~ArrayQueue() { delete[] a; }

	template<typename T>
	friend void printindex(ArrayQueue<T> q);
};

template<typename T>
void printindex(ArrayQueue<T> q) {
	std::cout << "backindex  " << q.backIndex << '\n';
	std::cout << "frontindex " << q.frontIndex << '\n';
	std::cout << "queueSize  " << q.queueSize << '\n';
	std::cout << "Size       " << q.Size << '\n';
}