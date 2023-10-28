#pragma once

/*
                        MATHEMATICS FUNCTION DEFINITION
                        1. INDICATOR FUNCTION
                        2. FACTORIAL FUNCTION
                        3.
*/

#include <cmath>
#include <algorithm>

using uint = unsigned int;

namespace Math {

    /////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //          INDICATOR AS FUNCTION
    // 
    /////////////////////////////////////////////////////////////////////////////////////////////////////////////

    template<typename T, template<typename, typename...>class Set>
    uint indicator(T x, const Set<T>& set) {
        if (set.contain(x)) return 1;
        return 0;
    }

    template<typename T,typename Set>
    uint indicator(T x, const Set& set) {

        if (set(x)) return 1;
        return 0;
    }

    template<typename T,typename...Ts>
    uint indicator(T x, bool(*Set)(T,Ts...),Ts&&...ts) {
       // static_assert(std::is_al) should T = all Ts... type.
        if (Set(x,ts...)) return 1;
        return 0;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //    FLOATING OPERATION 
    //      1. increment in float and double
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    float float_inc(float& f, int inc = 1) noexcept {

        *(int*)&f += f > 0 ? inc : -inc;

        return f;
    }

    double float_inc(double& f, int64_t inc = 1) noexcept {

        *(int64_t*)&f += f > 0 ? inc : -inc;

        return f;

    }

}