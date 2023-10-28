#pragma once
#include <iostream>
#include "ArrayUtility.h"
/* 
               1. Abstract List
               2. ArrayList 
               3. ArrayStack
               4. ArrayQueue
*/

/* 
               1. ABSTRACT DATA LIST WITH ARRAY
                  Operation :
                  1. empty();           true if it empty, false if not
                  2. size() ;           return size list
                  3. get(index);        return index th element
                  4. indexOf(x);        return the index of first occurrence element x, -1 if not.
                  5. erase(index);      remove/delete element in index.
                  6. insert(index, x);  insert x at index th element, 
                  7. output();          output the list from left to right.
*/
template<typename T>
class _List {

public:
    virtual ~_List() {}
    virtual bool empty() const = 0 ;
    virtual size_t size() const = 0 ;
    virtual T& at(size_t) const = 0 ;
    virtual size_t indexOf(const T&) const = 0 ;
    virtual void erase(size_t) = 0;
    virtual void insert(size_t, const T&) = 0;
    virtual void output() const = 0;

};

template<class T>
class ArrayList : public _List<T> {

protected:
    size_t capacity;
    size_t listSize;
    T* a;

public:
    ArrayList(size_t _capacity = 10) 
        :capacity{_capacity}
    {
        if (_capacity < 1) {
            std::cout << "Not correct capacity should be >= 10\n";
        }
        a = new T[capacity];
        listSize = 0;
    }

    ArrayList(const ArrayList<T> & list)
    {
        capacity = list.capacity;
        listSize = list.listSize;
        a = new T[capacity];
        std::copy(list.a, list.a + listSize, a);
    }

    ~ArrayList() { delete[] a; }
    
    bool empty() const {
        if(listSize == 0) return true;
        return false;
    }

    size_t size() const {
        return listSize;
    }

    T& at(size_t index) const {
        if (index < listSize) return a[index];
        std::cout << "index out of range\n";
        return a[listSize - 1];
    }

    size_t indexOf(const T& x) const {
       size_t index = (size_t) std::find(a, a + listSize, x);

       if (index == listSize) return -1;

       return index;
    }

    size_t _indexOf(const T& x)const {
        
        for (int i = 0; i < listSize; i++)
        {
            if (a[i] == x) {
                return i; 
                break;
            }
        }

        return -1;
    }

    void erase(size_t index) {
        if (index >= listSize) { std::cout << "index out of range\n"; return; }

        std::copy(a + index + 1, a + listSize, a + index);
        a[--listSize].~T();
    }

    void insert(size_t index, const T& x) {
        if (index > listSize)
        {
            std::cout << "index " << index << " out of range " << listSize << "\n";
            return;
        }

        if (listSize == capacity)
        {
            arrayResize<T>(a, capacity, 2 * capacity);
            capacity *= 2u;
        }

        std::copy_backward(a + index, a + listSize, a + listSize + 1);
        a[index] = x;
        listSize++;

    }

    void output() const {
        for (int i = 0; i < listSize; i++)
            std::cout << a[i] << " ";
        std::cout << "\nSize " << listSize << " Capacity "<< capacity << '\n';
    }


};