#pragma once

// Identity metafunction -----------------------------------------------------
template<class T>
struct type_is_ { using type = T; };


//----------------------------------------------------------------------------
//--------------- IS A NATURAL NUMBER METAFUNCTION TYPE ----------------------

template <typename T>
struct is_natural_number_ {  };

// partial specialization
//template<>
//struct is_natural_number_<Int>           :type_is_<Int>{};
								         
template<>						         
struct is_natural_number_<short>         : type_is_<short> {};
								         
template<>						         
struct is_natural_number_<int>           : type_is_<int> {};
									     
template<>							     
struct is_natural_number_<long int>      :type_is_<long int> {};

template<>
struct is_natural_number_<long long int> :type_is_<long long int> {};

template<>
struct is_natural_number_<unsigned short> :type_is_<unsigned short> {};

template<>
struct is_natural_number_<unsigned int> : type_is_<unsigned int> {};

template<>
struct is_natural_number_<unsigned long int> :type_is_<unsigned long int> {};

template<>
struct is_natural_number_<unsigned long long int> :type_is_<unsigned long long int> {};

// enable type if addicate

template<bool, typename T, typename>
struct enable_type_if { using type = T; };

template<typename T, typename U>
struct enable_type_if<false, T, U> { using type = U; };

template<typename T, typename U>
struct adequat_type_to : enable_type_if<(sizeof(T) > sizeof(U)), T, U> {};