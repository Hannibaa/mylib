#pragma once
#include <algorithm>
#include <functional>
#include <random>

/*
           THIS UTILITY IS FOR POINTER LIKE ARRAY WITH NEW AND DELETE
           1D ARRAY ALLOCATION AND RESIZE AND UTILITY 
           2D ARRAY ALLOCATION AND RESIZE AND ...
*/

//         DEFINE MACRO FOR STATIC ASSERT TYPE TRAITS OF TYPE ARITHMETIC
#define IS_ARITHMETIC       static_assert(std::is_arithmetic<T>::value , "should be arithmetic type")
#define IS_ARITHMETIC_T(T)  static_assert(std::is_arithmetic<T>::value , "should be arithmetic type")
#define ARRAY_  namespace Array{
#define _ARRAY  }

typedef unsigned int ui;

ARRAY_

template<typename T>
T* Operation1d(T*& a, ui size_a, T*& b, ui size_b,std::function<T(T,T)> Op)
{
   // static_assert(std::is_same<std::function<T(T, T)>, Operation>::value, "is not binary function");
    ui max_sz = std::max(size_a, size_b);
    ui min_sz = std::min(size_a, size_b);

    T* tmp = new T[max_sz];
    
    for (int i = 0; i < min_sz; i++)
        tmp[i] = Op(a[i], b[i]);

    if (size_a != size_b) {
        if (size_a > size_b)
            for (int i = min_sz; i < max_sz; i++) tmp[i] = a[i];
        else
            for (int i = min_sz; i < max_sz; i++) tmp[i] = b[i];
    }

    return tmp;
}

template<typename T>
T Scalar1dOperation(T*& a, ui size_a, T*& b, ui size_b, std::function<T(T, T)> Op)
{
    
}

template<typename T>
T* Add1d(T*& a,ui size_a, T*& b, ui size_b) {
    ui size = std::max(size_a, size_b);
    ui min_sz = std::min(size_a, size_b);
   T* tmp = new T[size]{};
   for (int i = 0; i < min_sz; i++)
       tmp[i] = a[i] + b[i];

   if (size_a > size_b)
       for (int i = min_sz ; i < size; i++)  tmp[i] = a[i];
            else for (int i = min_sz ; i < size; i++ ) tmp[i] = b[i];

   return tmp;
}

template<typename T>
T* Scalar1d(T* a, ui size, const T& scalar) {
    IS_ARITHMETIC_T(T);

    T* tmp = new T[size]{};

    for (int i = 0; i < size; i++)
    {
        tmp[i] = scalar * a[i];
    }

    return tmp;
}

/*
         1D ARRAY ALLOCATION AND RESIZE, DEALLOCATION UTILITY
*/

template<typename T>
void Alloc1d(T*& a, ui size, const T& a0 = T{}) {
    if (a != nullptr) { std::cout << "Should be new array with pointer nullptr \n"; return; }

    a = new T[size];

    for (ui i = 0; i < size; i++ ) a[i] = a0;
}

template<typename T>
void Dealloc1d(T*& a, ui size) {
    if (a == nullptr) { std::cout << "already deallocated \n"; return; }

    delete[] a;

    a = nullptr;
}

template<typename T>
void Resize1d(T*& a, size_t oldSize, size_t newSize)
{
    T* temp = new T[newSize];
    size_t sz = std::min(oldSize, newSize);
    std::copy(a, a + sz, temp);
    delete[] a;
    a = temp;

}

template<typename T> // No STL version
void Resize1dNSTL(T*& a, size_t oldSize, size_t newSize)
{
    T* temp = new T[newSize];
    size_t sz = oldSize < newSize ? oldSize : newSize;

    for (size_t i= 0; i < sz; i++)
    {
        temp[i] = a[i];
    }

    delete[] a;
    a = temp;
}

template<typename T>
T fgetRandom(T min, T max) {
    IS_ARITHMETIC;
    static_assert(std::is_floating_point<T>::value, "type should be floating point");
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_real_distribution<T> rrand(min, max);

    return rrand(gen);
}

template<typename T>
T igetRandom(T min, T max) {

    IS_ARITHMETIC;
    static_assert(std::is_integral<T>::value, "type should be integral type");
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution<T> irand(min, max);

    return irand(gen);
}


char cgetRandom(char min, char max) {
    return char(igetRandom<int>(int(min), int(max)));
}

template<typename T>
void Random1di(T*& a, ui size,T min, T max) {
    if (a != nullptr) { std::cout << "should be a void array \n"; return; }

    a = new T[size]{};

    for (int i = 0; i < size; i++)
        a[i] = igetRandom<T>(min,max);

}

template<typename T>
T* makeRand1d(ui size, const T& min, const T& max) {
    T* tmp = new T[size]{};

    for (int i = 0; i < size; i++)
        tmp[i] = igetRandom<T>(min, max);

    return tmp;
}

template<typename T>
T** makeRand2d(ui sizeX, ui sizeY, const T& min, const T& max) {

}
/*  
           2D ARRAY ALLOCATION AND RESIZE AND UTILITY
*/

template<typename T>
void array2dResize(T**& a, size_t oldSizeX, size_t oldSizeY, size_t newSizeX, size_t newSizeY)
{

}

template<typename T>
void Alloc2d(T**& a, size_t nRaw,size_t nColumn)
{
    if (a != nullptr) { std::cout << "Should be new array\n"; return; }

    T** temp = new T * [nRaw];
    for (size_t i = 0; i < nRaw; i++)
        temp[i] = new T[nColumn];
    a = temp;
}

template<typename T>
void Dealloc2d(T**& a, ui nRow, ui nCol)
{
    if (a == nullptr) { std::cout << "is already done\n"; return; }

    for (size_t i = 0; i < nRow; i++) delete[] a[i];

    delete a;

    a = nullptr;
}

template<typename T>
void Alloc2dVariable(T**& a, size_t nRaw, size_t* nColumn)
{
    if (a != nullptr) { std::cout << "Should be new array\n"; return; }

    T** temp = new T * [nRaw];
    for (size_t i = 0; i < nRaw; i++)
        temp[i] = new T[nColumn[i]];
    a = temp;

}


//template<typename T>
//void shiftArrayLeft(T*& a, size_t size, size_t index) {  // for heap section allocation
//    std::cout << "heap version called\n";
//    // condition that index < size;
//    if (index > size) { std::cout << "invalid index\n"; return; }
//
//    for (int i = index; i < size; i++)
//        a[i - index] = a[i];
//
//    for (int i = size - index; i < size; i++)
//        a[i].~T();
//}



template<typename T>
void shiftLeft(T* a, size_t size, size_t index) {  // for heap section allocation
    std::cout << "stack version called\n";
    // condition that index < size;
    if (index > size) { std::cout << "invalid index\n"; return; }

    for (int i = index; i < size; i++)
        (a)[i - index] = (a)[i];

    for (int i = size - index; i < size; i++)
        (a)[i].~T();
}

/*
                ARRAY CONVERT BETWEEN DIMENSION 1D AND 2D 
*/

template<typename T>
void Convert2d1d(const T**& a, ui size_x, ui size_y, T*& b) {
    
    T* tmp_b = new T[size_x * size_y]{};

    for (int i = 0; i < size_x; i++)
        for (int j = 0; j < size_y ; j++)
        {
            tmp_b[size_y * i + j] = a[i][j];
        }

    b = tmp_b;
}

template<typename T>
void Convert2d1d_(const T a[], ui size_x, ui size_y, T*& b) {

    T* tmp_b = new T[size_x * size_y]{};

    for (int i = 0; i < size_x; i++)
        for (int j = 0; j < size_y; j++)
        {
            tmp_b[size_y * i + j] = a[i][j];
        }

    b = tmp_b;
}


template<typename T>
void Convert1d2d(T*& a, ui size, T**& b, ui size_x, ui size_y)
{
    // sould be size = size_x + size_y;
    ui Size = size_x * size_y;
    if (Size != size);
}

template<typename T> 
void ConvertToHeap(const T (a)[], ui sizeX, ui sizeY = 0) {
    if (sizeY == 0) {

        return;
    }


}


void Make2Dmatrix(int*** mat, int N, int* M)
{
    // CHECKING THE SIZE COMPATIBILITY OF M SHOULD BE = TO N;
    if (sizeof(M) / sizeof(int) < N) { std::cout << "Size of M not equal to N\n"; return; }

    *mat = new int* [N];
    for (int i = 0; i < N; i++)
    {
        *mat[i] = new int[M[i]];
    }
}


/*
                                 PRINT FUNCTION
                1. 1D
                2. 2D
                3. 1D FOR STACK ALLOCATION []
                4. 2D FOR STACK ALLOCATION []
*/

template<typename T>
void print1d(T* a, size_t Size) {
    if (a == nullptr) { std::cout << "array not initialized or not allocated \n"; return; }

    for (size_t i = 0; i < Size; i++)
        std::cout << a[i] << " ";
    std::cout << '\n';
}

template<typename T>
void print1d(const T(&a)[], size_t Size) {
    if (a == nullptr) { std::cout << "array not initialized or not allocated \n"; return; }

    for (size_t i = 0; i < Size; i++)
        std::cout << a[i] << " ";
    std::cout << '\n';

}

template<typename T>
void print2d(const T**& a, size_t SizeX, size_t SizeY) {
    std::cout << " first function selected \n";
    for (size_t i = 0; i < SizeX; i++) {
        for (size_t j = 0; j < SizeY; j++)
            std::cout << a[i][j] << " ";
        std::cout << '\n';
    }
}

template<typename T>
void print2d( T (*a)[], ui SizeX, ui SizeY)
{
    std::cout << " second \n";
    for (size_t i = 0; i < SizeX; i++) {
        for (size_t j = 0; j < SizeY; j++)
            std::cout << a[i][j] << " ";
        std::cout << '\n';
    }

}

_ARRAY