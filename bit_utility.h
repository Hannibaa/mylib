/*             Authur  : KADDA Aoues 
               Library : Bit utility 
               Date    : ?? / ?? / 2023                         
                
*/

#pragma once
#include <utility>
#include <bit>
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//    TYPES AND MACROS
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////

using uchar = unsigned char;
using ushort = unsigned short;
using uint = unsigned int;
using byte = unsigned char;


const std::string Base16{ "0123456789abcdef" };


#define IS_COPYABLE(X)   std::is_trivially_copyable_v<X>
#define IS_POD(X)        std::is_pod_v<X>   // this is dipricated in new standard c++20;

// Color Macro And Macro conversion and masking

#define _RED(x)                 ((uchar)(x & 0x000000ff))
#define _GREEN(x)               ((uchar)((x & 0x0000ff00) >> 8 ))
#define _BLUE(x)                ((uchar)((x & 0x00ff0000) >> 16 ))
#define _ALPHA(x)               ((uchar)((x & 0xff000000) >> 24 ))

#define _CHAR_LL_INT            _RED
#define _CHAR_LH_INT            _GREEN
#define _CHAR_HL_INT            _BLUE
#define _CHAR_HH_INT            _ALPHA

#define _INTRED(x)              ((int(x)) & (0x000000ff))
#define _INTGREEN(x)            (((int(x))<<8) & (0x0000ff00))
#define _INTBLUE(x)             (((int(x))<<16) & (0x00ff0000))
#define _INTALPHA(x)            (((int(x))<<24) & (0xff000000))

#define _INT_L_INT64(X)         static_cast<int>(X & 0x0000'0000'ffff'ffff)
#define _INT_H_INT64(X)         static_cast<int>((X & 0xffff'ffff'0000'0000) >> 32)

// unsigned short to int and reverse Macro
#define _SHORT_L_INT(x)         static_cast<short>(x & 0x0000ffff)
#define _SHORT_H_INT(x)         static_cast<short>((x & 0xffff0000) >> 16 )

#define _SHORT_TO_LINT(x)       (int(x) & (0x0000ffff))
#define _SHORT_TO_HINT(x)       ((int(x)) << 16)

#define _CHAR_TO_LLINT(x)       (int(x) & (0x000000ff))
#define _CHAR_TO_LHINT(x)       (((int(x))<<8) & (0x0000ffff))
#define _CHAR_TO_HLINT(x)       (((int(x))<<16) & (0x00ffffff))
#define _CHAR_TO_HHINT(x)       ((int(x))<<24)

#define POWER2TYPE(TYPE,N)    ((TYPE)((TYPE)1 << (TYPE)N ))


namespace Bit {

    enum Bit { Zero = 0, One };

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //                           UNION TYPES.
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    requires std::is_trivially_copyable_v<T>
    union byte_type {
        T value;
        byte byte[N];
    };

    // Print operator
    template<typename T>
    requires std::is_trivially_copyable_v<T>
    std::ostream& operator << (std::ostream& os, byte_type<T> _data) {
        for (int i = 0; i < sizeof(T); i++) {
            os << (int)_data.byte[i] << " , ";
        }
        return os;
    }


    // Field of Bytes 
    template<size_t N>
    struct Byte_Field {
        byte Byte[N];

        byte& operator[](size_t i) {
            return Byte[i];
        }

        byte operator[](size_t i) const {
            return Byte[i];
        }
    };


    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //    BIT MASK FUNCTIONS
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    template<typename T, int from, int to, bool b = (to < 8 * sizeof(T) && from < to) >
    constexpr T make_bitMask() {
        //	if (!b) { std::cout << "out of range of size of type\n"; return T{}; }
        static_assert(b, "out of range of size of type");

        T x{};
        byte* pbyte = (byte*)&x;

        for (int i = from; i < to + 1; i++) {

            int _i = i / 8;
            int __i = i % 8;
            *(pbyte + _i) = *(pbyte + _i) | (1 << __i);
        }

        return x;
    };


    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //    get Subtype from T type at position n 
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    /*
              make general function that vectorization a type T to a SubType and extracted in a vector
              for exemple 
                     T |ffff|ffff|ffff|ffff| is 64 bits type and we want to extract to type char
                     and short and int 
                     int[2], short[4], char[8].
                     getSubType<char>(const T& x) -> char[8];
    */

    template<typename SubType, typename T, size_t N = sizeof(T)/sizeof(SubType)>
    requires std::is_trivially_copyable_v<T> && std::is_trivially_copyable_v<SubType>
                &&  ( sizeof(T) % sizeof(SubType) == 0 )
    auto  getSubType(const T& x) {
               
        std::array<SubType, N> t;

        std::memcpy(t.data(), &x, sizeof(T));

        return t;
    }

    template<typename SubType, typename T>
    requires std::is_trivially_copyable_v<T> && std::is_trivially_copyable_v<SubType>
             && (sizeof(T) >= sizeof(SubType))
    constexpr SubType _getSubType(const T& x, int _posbytes = 0) {
                 // check that reading position always stay inside variable x

                 SubType t{};
                 std::memcpy(&t, ((char*)&x) + _posbytes, sizeof(SubType));
                 return t;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //        GENERALIZATION OF PREVIOUS FUNCTION .
    //        This function designed like following : 
    //        |abc|defgs|gf| this struct of 10 char and 
    //        |012|34567|89| we want to get subtype (of 5 char) from 3;
    //        value of subtype is : defgs ;
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    template<typename SubType, typename IndexType = char, typename T>
    constexpr SubType getSubType_(const T& x, unsigned int n,unsigned int m = 0) {
        static_assert(std::is_trivially_copyable_v<T>, "T type should be trivially copyable");
        static_assert(std::is_trivially_copyable_v<SubType>, "SubType type should be trivially copyable");
        static_assert(std::is_trivially_copyable_v<IndexType>, "IndexType should be trivially copyable");
        static_assert(sizeof(IndexType) + sizeof(SubType) <= sizeof(T), "verify types size");

        // condition on integer n.
        if (n > (sizeof(T) / sizeof(SubType)) + sizeof(SubType) / sizeof(IndexType) - 2) {
            std::cout << "\n check the number n\n";
            return {};
        }

        SubType a{};
        std::memcpy(&a, (SubType*)((IndexType*)&x + n) + m, sizeof(SubType));

        return a;
    }

    //
    // templated or compile time getSubType function
    //
    template<typename SubType,size_t N,size_t M , typename IndexType = char, typename T>
    constexpr SubType getSubType_(const T& value) {
        return getSubType_<SubType, IndexType, T>(value, N, M);
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //        SET SUBTYPE INSIDE LONGER TYPE WITH INDICATING A POSITION IN BYTE.
    //        RETURNE A CHANGED TYPE
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    template<typename T, typename SubType>
    T setSubType(const SubType& sub_value, T value, unsigned int position) {
        static_assert(std::is_trivially_copyable_v<T>, "T type should be trivially copyable");
        static_assert(std::is_trivially_copyable_v<SubType>, "SubType type should be trivially copyable");
        static_assert(sizeof(T) > sizeof(SubType), "SubType size is greater than type T");

        // condition for number n ;
        if (position > (sizeof(T) / sizeof(SubType)) + sizeof(SubType) - 2) {
            std::cout << "\n check the number n\n";
            return {};
        }


        std::memcpy((char*)&value + position, &sub_value, sizeof(SubType));

        return value;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //    LOADING ANY TYPE TO VECTOR OF BYTES
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    template<typename T>
    std::vector<byte> load_toVector(const T& x) {

        std::vector<byte> vec(sizeof(T));
        std::memcpy(vec.data(), &x, sizeof(T));
        return vec;
    }


    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //    MAKE A NEW TYPE FROM CONTENGIOUS MEMORY ARRAY OF BYTE
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    // 1. making one element
    template<typename T, typename Array>
        requires requires(Array A) {
        requires sizeof(typename Array::value_type) == 1;
        A.data();
    }
    constexpr T make_data_from(const Array& vec, size_t position) {

        // add condition about positioning and size of vectors
        if (position + sizeof(T) > vec.size()) {
            std::cout << "overflow ; check position and size of variable\n";
            return {};
        }

        T t{};
        std::memcpy(&t, vec.data() + position, sizeof(T));
        return t;
    }

	template<typename T, typename Array>
		requires requires(Array A) {
		requires sizeof(typename Array::value_type) == 1;
	    A.data(); 
	}
	std::vector<T> make_data_from(const Array& vec) {
		// check if size of T > than size of vec
		if (vec.size() < sizeof(T)) {
			std::cout << "we can't make type\n";
			return {};
		}

		// we should make calculation : 
		// size of vector / size of T :
		size_t size = vec.size() / sizeof(T);

		std::vector<T> result(size);
		std::memcpy(result.data(), vec.data(), size * sizeof(T));

		return result;
	}



        

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

        ut _ut{};
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
	constexpr Resultype

		make_type_c(const Tlo& x, const Thi& y)
	{
		// all type here should be integer type or arithmetic type build-in type
		// we need Meta-programming for this concepts
		// may be use concepts from standard library
		static_assert(sizeof(Resultype) >= sizeof(Tlo) + sizeof(Thi));
		static_assert(std::is_trivially_copyable_v<Resultype> &&
			std::is_trivially_copyable_v<Tlo> &&
			std::is_trivially_copyable_v<Thi>, "Should be a copyable types");


		Resultype z{};
		byte* pTlo = (byte*)&x;
		byte* pThi = (byte*)&y;
		byte* pz = (byte*)&z;

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

    //     MAKING A TYPE USING MEMCPY
    template< typename Resultype, typename Tlo, typename Thi>
    constexpr Resultype 
        make_type_memcpy(const Tlo& x, const Thi& y)
    {
        // all type here should be integer type or arithmetic type build-in type
        // we need Meta-programming for this concepts
        // may be use concepts from standard library
        static_assert(sizeof(Resultype) >= sizeof(Tlo) + sizeof(Thi));
        static_assert(std::is_trivially_copyable_v<Resultype> &&
            std::is_trivially_copyable_v<Tlo> &&
            std::is_trivially_copyable_v<Thi>, "Should be a copyable types");

        Resultype R{}; 
        std::memcpy(&R, &x, sizeof(Tlo));
        std::memcpy(((byte*) & R) + sizeof(Tlo), &y, sizeof(Thi));

        return R;
    }

    // Making using C++ technic 
        //     MAKING A TYPE USING STRUCT 
    template< typename Resultype, typename Tlo, typename Thi>
    constexpr Resultype
        make_type_struct(const Tlo& x, const Thi& y)
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
        
        result.xhi = y;
        result.xlo = x;

        return std::bit_cast<Resultype>(result);
    }


    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //    Splite a Type T to two (2) types Thi, Tlo.
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////


    template<typename ResulThi, typename ResulTlo, typename T>
    constexpr std::pair<ResulThi, ResulTlo>

        splite_type_c(T x) {

        static_assert(std::is_trivially_copyable<T>::value
            && std::is_trivially_copyable<ResulThi>::value
            && std::is_trivially_copyable<ResulTlo>::value, "Should be all type a pod or");

        static_assert(!std::is_pointer<T>::value
            && !std::is_pointer<ResulThi>::value
            && !std::is_pointer<ResulTlo>::value, "Should not be pointer");

        static_assert((sizeof(ResulThi) + sizeof(ResulTlo) == sizeof(T)), "mismatch of size of result type");

        int nlo = sizeof(ResulTlo);
        int nhi = sizeof(ResulThi);

        ResulThi xhi{};
        byte* pbyte = (byte*)&x, * phi = (byte*)&xhi;
        ResulTlo* pxlo = (ResulTlo*)&x;

        for (int i = 0; i < nhi; i++)
        {
            *(phi + i) = *(pbyte + i + nlo);
        }

        return std::make_pair(*pxlo, xhi);
    }

    // second aproche is 

    template<typename Tlo, typename Thi, typename T>
    constexpr std::pair<Tlo, Thi>
        splite_type(T x) {
        static_assert(std::is_trivially_copyable_v<T>
                     && std::is_trivially_copyable_v<Thi>
                     && std::is_trivially_copyable_v<Tlo>, "Should be all type a pod or");

        static_assert(!std::is_pointer<T>::value
            && !std::is_pointer<Thi>::value
            && !std::is_pointer<Tlo>::value, "Should not be pointer");

        static_assert((sizeof(Thi) + sizeof(Tlo) == sizeof(T)), "mismatch of size of result type");

        struct Tspliter {
            Tlo xlo;
            Thi xhi;
        };

        Tspliter _x = std::bit_cast<Tspliter>(x);
        return std::make_pair(_x.xlo, _x.xhi);
    }



    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //        4. Get a Bytes and bits 1658-2025
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    
    //   Get bits of type using C-style
    template<typename T, int N = sizeof(T)>
    int get_bit_at_c(T x, int n) {
        if (n < 0 || n > N * 8) { std::cout << "number of bit is out of size of type\n"; return T{}; }

        byte* pbyte = (byte*)&x;

        int _n = n / 8;
        int __n = n % 8;

        _n = (*(pbyte + _n) & (1 << __n)) >> __n;

        return _n;
    }



    //    Helper function return array of 8 int of bit of type char or 8 bit types
    template<typename Integer = int,typename type8bits>
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
        byte* pbyte = (byte*)&t;

        int _n =  int(n) / 8;
        int __n = int(n) % 8;

        _n = (*(pbyte + _n) & (1 << __n)) >> __n;

        return static_cast<Integer>(_n);
    }

    //    that function return an array of bits put it in Integer type
    template<typename Integer = int ,typename T, size_t Size = sizeof(T)>
    std::array<Integer, Size * 8>

        bits(const T& t) {

        static_assert(IS_COPYABLE(T), "type should be POD and copyable");
        static_assert(std::is_integral_v<Integer>, "type of bit should be integer type");

        std::array<Integer, Size * 8> bit_array{};

        Byte_Field<Size> bytes = std::bit_cast<Byte_Field<Size>>(t);

        for (int i = 0; i < Size; ++i) {
            std::array<int, 8> temp = get_bits_byte<int>(bytes[i]);
            for (int j = 0; j < 8; ++j)
                bit_array[j + i*8] = Integer(temp[j]);
        }

        return bit_array;
    }

    ////////// Get byte C-Style
    template<typename T, int N = sizeof(T)>
    byte get_byte_at_c(T x, int n) {

        if (n < 0 || n > N) { std::cout << "number of bit is out of size of type\n"; return T{}; }

        byte* pbyte = (byte*)&x;

        return *(pbyte + n);
    }


    ////////// Byte getter function;
    template<typename Integer = byte ,typename T, size_t Size = sizeof(T)>
    constexpr Integer

        byte_n(const T& t, size_t n) {
       
       // static_assert(IS_POD(T), "type should be pod type");
        static_assert(std::is_integral_v<Integer>, "type should be integer type");
        static_assert(IS_COPYABLE(T), "type should be copyable type");

        return static_cast<Integer>(std::bit_cast<Byte_Field<Size>>(t).byte[n]);
    }


    ///////// get bytes as in array
    template<typename Integer = byte, typename T, size_t Size = sizeof(T)>
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
    void bit_permetation(const T& t){}

    template<typename T>
    void byte_permutation(const T& t){}

    template<typename T>
    void bit_random_permute(T& t) {};

    template<typename T>
    void byte_random_permute(T& t) {};


    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //     Bit operation with macro 
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    constexpr std::pair<short, short> uint2u2short(uint n) {

        return std::make_pair(_SHORT_L_INT(n), _SHORT_H_INT(n));

    }

    constexpr int u2short2uint(short s1, short s2) {

        return _SHORT_L_INT(s1) | _SHORT_H_INT(s2);

    }

    template<typename Trgb>
    constexpr int rgb2int(const Trgb& color) {
        return  _INTGREEN(color.green) | _INTBLUE(color.blue) | _INTRED(color.red);
    }

    template<typename Trgb>
    constexpr Trgb int2rgb(int n) {      // r g b

        return Trgb{ .red = _RED(n),.green = _GREEN(n), .blue = _BLUE(n) };
    }

    ///////////////////////////////// to hexadecimal convertion /////////////////////////////////////////

    std::string toHex(char c) {

        return "0x" + std::string{ Base16[(c & 0xf0) >> 4] } + std::string{ Base16[c & 0x0f] };

    }

    std::string toHex(short s) {

        return "0x" + std::string{ Base16[(s & 0xf000) >> 12] } + std::string{ Base16[(s & 0x0f00) >> 8] }
        + std::string{ Base16[(s & 0x00f0) >> 4] } + std::string{ Base16[s & 0x000f] };

    }

}
