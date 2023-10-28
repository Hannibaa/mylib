#pragma once
#include <vector>
#include <array>
#include <string>
#include <type_traits>

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
#pragma waring(disable : 4996)
#define IS_POD(X)        std::is_pod_v<X>

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

#define _CHAR_LL_INT    _RED
#define _CHAR_LH_INT    _GREEN
#define _CHAR_HL_INT    _BLUE
#define _CHAR_HH_INT    _ALPHA

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
    //                 3. MAKING A NEW TYPES
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    // Making using C++ technic 
        //     MAKING A TYPE USING MEMCPY
    template< typename Resultype, typename Tlo, typename Thi>
    constexpr Resultype

        make_type_cpp(const Tlo& x, const Thi& y)

    {
        // all type here should be integer type or arithmetic type build-in type
        // we need Meta-programming for this concepts
        // may be use concepts from standard library
        static_assert(sizeof(Resultype) >= sizeof(Tlo) + sizeof(Thi));
        static_assert(std::is_trivially_copyable_v<Resultype> &&
            std::is_trivially_copyable_v<Tlo> &&
            std::is_trivially_copyable_v<Thi>, "Should be a copyable types");

        Resultype R{};
        struct TloThi {
            Tlo xlo;
            Thi xhi;
        };

        TloThi result{};

        result.xhi = x;
        result.xlo = y;

        return std::bit_cast<Resultype>(result);
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //      SPLITE A TYPE TO PAIR OF TYPES   
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

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

    //   Get bits of type using C-style
    template<typename T, int N = sizeof(T)>
    int get_bit_at_c(T x, int n) {
        if (n < 0 || n > N * 8) { std::cout << "number of bit is out of size of type\n"; return T{}; }

        Byte* pbyte = (Byte*)&x;

        int _n = n / 8;
        int __n = n % 8;

        _n = (*(pbyte + _n) & (1 << __n)) >> __n;

        return _n;
    }



    //    Helper function return array of 8 int of bit of type
    template<typename Integer = int, typename type8bits>
    std::array<Integer, 8> get_bits_byte(type8bits b) {

        static_assert(sizeof(type8bits) == 1, "should be have 1 byte or 8 bits");
        static_assert(std::is_integral_v<Integer>, "this type should be integer type");

        std::array<Integer, 8> bit_array{};

        for (size_t i = 0; i < 8; i++)
            bit_array[i] = Integer((b & (1 << i)) >> i);

        return bit_array;
    }


    //    that function get a bit and bytes from a type value
    template<typename Integer = int, typename T, size_t Size = sizeof(T)>
    constexpr Integer

        bit_n(const T& t, size_t n) {

        static_assert(IS_COPYABLE(T), "type should be POD and copyable");
        static_assert(std::is_integral_v<Integer>, "type of bit should be integer type");

        if (n > Size * 8) return {};

        // using C style better
        Byte* pbyte = (Byte*)&t;

        int _n = int(n) / 8;
        int __n = int(n) % 8;

        _n = (*(pbyte + _n) & (1 << __n)) >> __n;

        return static_cast<Integer>(_n);
    }

    //    that function return an array of bits put it in Integer type
    template<typename Integer = int, typename T, size_t Size = sizeof(T)>
    std::array<Integer, Size * 8>

        bits(const T& t) {

        static_assert(IS_COPYABLE(T), "type should be POD and copyable");
        static_assert(std::is_integral_v<Integer>, "type of bit should be integer type");

        std::array<Integer, Size * 8> bit_array{};

        Byte_Field<Size> bytes = std::bit_cast<Byte_Field<Size>>(t);

        for (int i = 0; i < Size; ++i) {
            std::array<int, 8> temp = get_bits_byte<int>(bytes[i]);
            for (int j = 0; j < 8; ++j)
                bit_array[j + i * 8] = Integer(temp[j]);
        }

        return bit_array;
    }

    ////////// Get byte C-Style
    template<typename T, int N = sizeof(T)>
    Byte get_byte_at_c(T x, int n) {

        if (n < 0 || n > N) { std::cout << "number of bit is out of size of type\n"; return T{}; }

        Byte* pbyte = (Byte*)&x;

        return *(pbyte + n);
    }


    ////////// Byte getter function;
    template<typename Integer = Byte, typename T, size_t Size = sizeof(T)>
    constexpr Integer

        byte_n(const T& t, size_t n) {

        // static_assert(IS_POD(T), "type should be pod type");
        static_assert(std::is_integral_v<Integer>, "type should be integer type");
        static_assert(IS_COPYABLE(T), "type should be copyable type");

        return static_cast<Integer>(std::bit_cast<Byte_Field<Size>>(t).byte[n]);
    }

    ///////// get bytes as in array
    template<typename Integer = Byte, typename T, size_t Size = sizeof(T)>
    constexpr std::array<Integer, Size>

        bytes(const T& t) {

        static_assert(std::is_integral_v<Integer>, "type should be integer type");
        static_assert(IS_COPYABLE(T), "type should be copyable type");

        std::array<Integer, Size> array_{};
        Byte_Field<Size> bf = std::bit_cast<Byte_Field<Size>>(t);

        for (int i = 0; i < Size; ++i) array_[i] = static_cast<Integer>(bf.byte[i]);

        return array_;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //      SET FUNCTION OF BIT AND BYTE
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    /////////// set bit at position 

    template<typename T, int N = sizeof(T)>  // use union 
    T set_bit_at_c(T x, int n) {
        if (n < 0 || n > N) { std::cout << "number of bit is out of size of type\n"; return T{}; }

        byte_type<T> byte_t;
        byte_t.type = x;
        int _n = n / 8;
        int __n = n % 8;
        byte_t.byte[_n] = byte_t.byte[_n] | (1 << __n);

        x = byte_t.value;
        return x;
    }


    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //    BIT AND BYTES PERMETATION, SWAPING,...
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    void bit_permetation(const T& t) {}

    template<typename T>
    void byte_permutation(const T& t) {}

    template<typename T>
    void bit_random_permute(T& t) {};

    template<typename T>
    void byte_random_permute(T& t) {};

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
