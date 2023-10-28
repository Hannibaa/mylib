#pragma once
#include <type_traits>
#include <MyLib/bit_utility.h>

/* 
*       JUST TO REMEMBER
    "MUSIC 'THOMAS WESLEY : CHAPTER 2
        1. USE ME
*/


#define _NODISCARD [[nodiscard]]
#define _STD       ::std::

/* 
          IN THIS HEADER WE WILL DEFINE A HELPER FUNCTION THAT IS USED HERE FOR 
       1. <bit>
       2. <bitset>
       3. <set>
       4. another existing files header that is used with Linux and Windows.

*/

template<typename T>
constexpr auto _swap_bytes(T value, unsigned int criteria) {

    return {};
}

template<typename T>
constexpr auto _reverse_bytes(T value); 

template<typename T>
constexpr auto _reverse_bits(T value);

template<typename T, typename Permetation>
constexpr auto _swap_bits(T value, const Permetation& permetation);

template<typename T, T Pattern>     // here T should be trivially copyllable
constexpr auto _generate_permetation(T value) {
    static_assert(std::is_trivially_copyable_v<T>, "Type T Should copyable type");

    return {}
}


_NODISCARD constexpr bool is_constant_evaluated() noexcept {
    return __builtin_is_constant_evaluated();
}


_NODISCARD constexpr unsigned long long _Byteswap_uint64(const unsigned long long _Val) noexcept {
    if ( is_constant_evaluated()) {
        return (_Val << 56) | ((_Val << 40) & 0x00FF'0000'0000'0000) | ((_Val << 24) & 0x0000'FF00'0000'0000)
            | ((_Val << 8) & 0x0000'00FF'0000'0000) | ((_Val >> 8) & 0x0000'0000'FF00'0000)
            | ((_Val >> 24) & 0x0000'0000'00FF'0000) | ((_Val >> 40) & 0x0000'0000'0000'FF00) | (_Val >> 56);
    }
    else {
        return _byteswap_uint64(_Val);
    }
}
