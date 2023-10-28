#pragma once
#include <vector>
#include <array>
#include <string>

/*
      This header file contain function that manipulate a bit of trivial Type or structure, without care about
      how structure designed intern, also may modifie pointer!!, 

      1. here we writing all possible of function version in C, C++, with differente algorithm 
      2. most of algorith is taken from lecture in CPPCON, CPPNow... 
      
      Here in code we have five section
          
          1. types and macros
          2. converting between types and c and c++ functions
          3. making a type from another types.
          4. get a byte from type or get <type> from a <type>
          5. set a byte and bit on types.

*/

namespace Bit {

#define IS_COPYABLE(X)   std::is_trivially_copyable_v<X>

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //                           1. TYPES AND STRUCTURE AND MACROS
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

// Color Macro And Macro conversion and masking

#define _RED(x)       (uchar)(x & 0x000000ff)
#define _GREEN(x)     (uchar)((x & 0x0000ff00) >> 8 )
#define _BLUE(x)      (uchar)((x & 0x00ff0000) >> 16 )
#define _ALPHA(x)     (uchar)((x & 0xff000000) >> 24 )

#define _CHAR_LL_INT(x)    _RED(x)
#define _CHAR_LH_INT(x)    _GREEN(x)
#define _CHAR_HL_INT(x)    _BLUE(x)
#define _CHAR_HH_INT(x)    _ALPHA(x)

#define _INTRED(x)    (int(x))
#define _INTGREEN(x)  ((int(x))<<8)
#define _INTBLUE(x)   ((int(x))<<16)

#define _INT_L_INT64(X) 
#define _INT_H_INT64(X) 

// unsigned short to int and reverse Macro
#define _SHORT_L_INT(x)       (short(x & 0x0000ffff))
#define _SHORT_H_INT(x)       (short((x & 0xffff0000) >> 16 ))

#define _SHORT_TO_LINT(x)     (int(x) & (0x0000ffff))
#define _SHORT_TO_HINT(x)     ((int(x)) << 16)

#define _CHAR_TO_LLINT(x)     (int(x) & (0x000000ff))
#define _CHAR_TO_LHINT(x)     (((int(x))<<8) & (0x0000ffff))
#define _CHAR_TO_HLINT(x)     (((int(x))<<16) & (0x00ffffff))
#define _CHAR_TO_HHINT(x)     ((int(x))<<24)

    using uchar = unsigned char;
    using ushort = unsigned short;
    using uint = unsigned int;
    using Byte = unsigned char;

    const std::string Base16{ "0123456789abcdef" };

    enum Bit { Zero = 0, One };

    // integer 32 bit to float 32 union
    union int_float {
        unsigned int i;
        float f;
    };

    // integer 64 bit to float 64 bit union
    union int64_double {
        int64_t i;
        double d;
    };

    // Union between field of byte and type T
    template<typename T, int N = sizeof(T)>
    union byte_type {
        T value;
        Byte byte[N];
    };

    // Print operator
    template<typename T>
    std::ostream& operator << (std::ostream& os, byte_type<T> _data) {
        for (int i = 0; i < sizeof(T); i++) {
            os << (int)_data.byte[i] << " , ";
        }
        return os;
    }



    // Field of Bytes 
    template<size_t N>
    struct Byte_Field {
        Byte byte[N];

        Byte& operator[](size_t i) {
            return byte[i];
        }
    };


    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //    BIT MASK FUNCTIONS
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
#define makeBitMask make_bitMask 

    template<typename T, int from, int to, bool b = (to < 8 * sizeof(T) && from < to) >
    constexpr T make_bitMask() {
        //	if (!b) { std::cout << "out of range of size of type\n"; return T{}; }
        static_assert(b, "out of range of size of type");

        T x{};
        Byte* pbyte = (Byte*)&x;

        for (int i = from; i < to + 1; i++) {

            int _i = i / 8;
            int __i = i % 8;
            *(pbyte + _i) = *(pbyte + _i) | (1 << __i);
        }

        return x;
    };


    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    //                                                                                                      //
    //                                         2. BIT CASTING                                               //
    //                                                                                                      //
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

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

    template<typename T, typename U>
    T bit_cast_union(const U& u) {
        static_assert(sizeof(T) == sizeof(U), "should be some size");
        static_assert(std::is_trivially_copyable_v<T> && std::is_trivially_copyable_v<U>, "should be POD and copyable");

        byte_type<T> t;
        byte_type<U> _u;

        _u.value = u;
        for (int i = 0; i < sizeof(U); ++i) t.byte[i] = _u.byte[i];

        return t.value;
    }

    template<typename T, typename U>
    T bit_cast_union2(const U& u) {
        static_assert(sizeof(T) == sizeof(U), "should be some size");
        static_assert(std::is_trivially_copyable_v<T> && std::is_trivially_copyable_v<U>, "should be POD and copyable");

        union ut {
            T ut;
            U uu;
        };

        ut _ut;
        _ut.uu = u;

        return _ut.ut;
    }



    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //                 3. MAKING A NEW TYPES
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////


    //    Making new type from two types, by using c-styles

    template< typename Resultype, typename Tlo, typename Thi>
    constexpr Resultype make_type_c(const Tlo& x, const Thi& y) {
        // all type here should be integer type or arithmetic type build-in type
        // we need Meta-programming for this concepts
        // may be use concepts from standard library
        static_assert(sizeof(Resultype) >= sizeof(Tlo) + sizeof(Thi));
        static_assert(std::is_trivially_copyable_v<Resultype> && 
                      std::is_trivially_copyable_v<Tlo> &&
                      std::is_trivially_copyable_v<Thi>, "Should be a copyable types");


        Resultype z{};
        Byte* pTlo = (Byte*)&x;
        Byte* pThi = (Byte*)&y;
        Byte* pz = (Byte*)&z;

        for (int i = 0; i < sizeof(Tlo); i++)
        {
            *(pz + i) = *(pTlo + i);
        }
        for (int i = 0; i < sizeof(Thi); i++)
        {
            *(pz + i + sizeof(Tlo)) = *(pThi + i);
        }

        return z;
    }


    //     Splite a type to two types by using c-style

    template<typename ResulThi, typename ResulTlo, typename T>
    constexpr std::pair<ResulThi, ResulTlo>
        splite_type(T x) {
        static_assert(std::is_pod<T>::value
            && std::is_pod<ResulThi>::value
            && std::is_pod<ResulTlo>::value, "Should be all type a pod or");

        static_assert(!std::is_pointer<T>::value
            && !std::is_pointer<ResulThi>::value
            && !std::is_pointer<ResulTlo>::value, "Should not be pointer");

        static_assert((sizeof(ResulThi) + sizeof(ResulTlo) <= sizeof(T)), "mismatch of size of result type");

        int nlo = sizeof(ResulTlo);
        int nhi = sizeof(ResulThi);

        ResulThi xhi{};
        Byte* pbyte = (Byte*)&x, * phi = (Byte*)&xhi;
        ResulTlo* pxlo = (ResulTlo*)&x;

        for (int i = 0; i < nhi; i++)
        {
            *(phi + i) = *(pbyte + i + nlo);
        }

        return std::make_pair(*pxlo, xhi);
    }




    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //        4. Get a Bytes and bits 
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    //    Helper function return array of 8 int of bit of type
    template<typename type8bits>
    std::array<int, 8> get_bits_byte(type8bits b) {

        static_assert(sizeof(type8bits) == 1, "should be have 1 byte or 8 bits");

        std::array<int, 8> bit_array{};

        for (size_t i = 0; i < 8; i++)
            bit_array[i] = int((b & (1 << i)) >> i);
        
        return bit_array;
    }


    //    that function get a bit and bytes from a type value
    template<typename Integer, typename T, size_t Size = sizeof(T)>
    constexpr Integer bitn(const T& t, size_t n) {

        static_assert(IS_COPYABLE(T), "type should be POD and copyable");
        static_assert(std::is_integral_v<Integer>, "type of bit should be integer type");



        return{};
    }

    //    that function return an array of bits put it in Integer type
    template<typename Integer,typename T, size_t Size = sizeof(T)>
    constexpr std::array<Integer, Size * 8> bit(const T& t) {

        static_assert(IS_COPYABLE(T), "type should be POD and copyable");
        static_assert(std::is_integral_v<Integer>, "type of bit should be integer type");

        std::array<Integer, Size * 8> bit_array{};

        Byte_Field<Size> bytes = std::bit_cast<Byte_Field<Size>>(t);

        for (int i = 0; i < Size; ++i) {
            std::array<int, 8> temp = get_bits_byte(bytes[i]);
            for (int j = 0; j < 8; ++j)
                bit_array[j + i] = Integer(temp[j]);
        }

        return bit_array;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //    Printing functions
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    template<typename T>
    void print_vector(std::vector<T> v, int Nline = 10) {

        for (int i = 0; i < v.size(); i++) {
            std::cout << v[i] << " , ";
            if (i% Nline = Nline - 1) std::cout << '\n';
        }

    }

    template<typename Container>
    void print_container(Container C, int Nline = 10) {
        
        int i{};
        for (auto& element : C) {
            std::cout << element << " , ";
            if (i % Nline == Nline - 1) std::cout << '\n';
            ++i;
        }

    }

}
