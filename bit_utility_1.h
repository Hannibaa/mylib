#pragma once
#include <vector>
#include <array>
#include <string>
#include <type_traits>

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
    

}
