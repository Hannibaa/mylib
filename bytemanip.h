#pragma once
#include <type_traits>

/* 
       FUNCTIONS :
         1. bit_cast
         2. byte_cast
         3. word_cast
         4. any_cast
*/

using uchar = unsigned char;
using ushort = unsigned short;
using uint = unsigned int;

// color Macro
#define _RED(x)       (uchar)(x & 0x000000ff)
#define _GREEN(x)     (uchar)((x & 0x0000ff00) >> 8 )
#define _BLUE(x)      (uchar)((x & 0x00ff0000) >> 16 )
#define _ALPHA(x)     (uchar)((x & 0xff000000) >> 24 )

#define _INT_LL(x)    _RED(x)
#define _INT_LH(x)    _GREEN(x)
#define _INT_HL(x)    _BLUE(x)
#define _INT_HH(x)    _ALPHA(x)

#define _INTRED(x)    (int(x))
#define _INTGREEN(x)  ((int(x))<<8)
#define _INTBLUE(x)   ((int(x))<<16)

// unsigned short to int and reverse Macro

#define _SHORT_L_INT(x)       (short(x & 0x0000ffff))
#define _SHORT_H_INT(x)       (short((x & 0xffff0000) >> 16 ))

#define _SHORT_TO_LINT(x)     (int(x) & (0x0000ffff))
#define _SHORT_TO_HINT(x)     ((int(x)) << 16)

#define _CHAR_TO_LLINT(x)     (int(x) & (0x000000ff))
#define _CHAR_TO_LHINT(x)     (((int(x))<<8) & (0x0000ffff))
#define _CHAR_TO_HLINT(x)     (((int(x))<<16) & (0x00ffffff))
#define _CHAR_TO_HHINT(x)     ((int(x))<<24)

namespace Bit {

    using Byte = unsigned char;

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //    BIT_CAST FOR C METHODE AND OTHER WITH MEMCPY AND UNION
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    template<typename T, typename U>
    constexpr T bit_cast_c(U u) noexcept {

        static_assert(sizeof(T) == sizeof(U), "casting size should be superior or equal to casted size");
        static_assert(std::is_trivially_copyable_v<T> && std::is_trivially_copyable_v<U>, "type should be copyable");

        T t = *(T*)&u;

        return t;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //    BIT_CAST WITH MEMCPY
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    template<typename To, typename From>
    To bit_cast_memcpy(const From& from) noexcept {
        static_assert(sizeof(To) == sizeof(From), "should be some size");
        static_assert(std::is_trivially_copyable_v<To> && std::is_trivially_copyable_v<From>, "should be POD and copyable");

        To to{};

        std::memcpy(&to, &from, sizeof(To));

        return to;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //    BIT CAST USING UNION .
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////


    template<typename T, int N = sizeof(T)>
    union byte_type {
        T value;
        Byte byte[N];
    };

#ifndef BYTE_FIELD
#define BYTE_FIELD
    template<size_t N>
    struct Byte_Field {
        Byte byte[N];

        Byte& operator[](size_t i) {
            return byte[i];
        }
    };
#endif

    template<size_t N>
    struct Hex_field {
        short hex[N];

        short& operator[](size_t i) {
            return hex[i];
        }
    };

    template<typename T>
    Byte_Field<sizeof(T)>  get_bytes_of(const T& t) {
        return std::bit_cast<Byte_Field<sizeof(T)>>(t);
    }

    template<typename T>
    void printUnion(const byte_type<T>& bytes) {
        for (int i = 0; i < sizeof(T); i++) std::cout << i << " byte : " << (int)bytes.byte[i] << '\n';
    }

    // Byte type holder
    template<typename T, size_t Size = sizeof(T)>
    class Byte_type {
        T value;

    public:

        Byte& operator[](size_t i) {
            if (i < Size)
                return std::bit_cast<Byte_Field<Size>>(value)[i];
        }
    };

}