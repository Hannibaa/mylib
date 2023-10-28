#pragma once
/*
    1. Circular function -- javidx9 -- idea 
    2. Circular number class 
    3. addition functions can helps as is circular function with times
*/

#include <chrono>

template<typename TL, typename TR>
constexpr auto circ_add(TL a, TR b, const decltype(a+b)& min = 0, const decltype(a+b)& max = 360)
{
    auto result = a + b;
    auto range = max - min;
    while (result >= max) result -= range;
    while (result < min ) result += range;

    return result;
}

// circular function that can take any value and put it in interval min max;
template<typename T>
constexpr T circular(T a, const T& min = T{ 0 }, const T& max = T{ 360 })
{
    auto range = max - min;
    while (a >= max) a -= range;
    while (a < min ) a += range;

    return a;
}

template<typename T,T Period>
constexpr T circular(T a) {
    return circular<T>(a, T{}, Period);
}

