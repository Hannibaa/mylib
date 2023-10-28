#pragma once

template<typename T>
char get_char(const T& x, unsigned int n) {
	static_assert(std::is_trivially_copyable_v<T>, "T type should be trivially copyable");

	char a{};
	std::memcpy(&a, (char*)&x + n, 1);

	return a;
}


template<typename SubType, typename T>
constexpr SubType getSubType(const T& x, unsigned int n) {
	static_assert(std::is_trivially_copyable_v<T>, "T type should be trivially copyable");
	static_assert(std::is_trivially_copyable_v<SubType>, "SubType type should be trivially copyable");

	// condition on integer n 
	if (n > sizeof(T) / sizeof(SubType) - 1) {
		std::cout << "\n check the number n\n";
		return {};
	}

	SubType a{};
	std::memcpy(&a, (SubType*)&x + n, sizeof(SubType));

	return a;
}

template<typename SubType, size_t N, typename T>
constexpr SubType getSubType(const T& x) {
	static_assert(N < sizeof(T) / sizeof(SubType), "check a position value N");
	return getSubType<SubType>(x, N);
}

// get subType generalized

template<typename SubType,typename IndexType = char, typename T>
constexpr SubType getSubType_(const T& x, unsigned int n, unsigned int m = 0) {
	static_assert(std::is_trivially_copyable_v<T>, "T type should be trivially copyable");
	static_assert(std::is_trivially_copyable_v<SubType>, "SubType type should be trivially copyable");
	static_assert(std::is_trivially_copyable_v<IndexType>, "IndexType should be trivially copyable");
	static_assert(sizeof(IndexType) + sizeof(SubType) <= sizeof(T), "verify types size");

	// condition on integer n 
	if (n > (sizeof(T) / sizeof(SubType)) + sizeof(SubType) / sizeof(IndexType) - 2) {
		std::cout << "\n check the number n\n";
		return {};
	}

	SubType a{};
	std::memcpy(&a, (SubType*)((IndexType*)&x + n)+m, sizeof(SubType));

	return a;
}



// set subType inside another type(at any position index in term of char)
template<typename T, typename SubType>
T setSubType(const SubType& sub_value, T& value, unsigned int position) {
	static_assert(std::is_trivially_copyable_v<T>, "T type should be trivially copyable");
	static_assert(std::is_trivially_copyable_v<SubType>, "SubType type should be trivially copyable");
	static_assert(sizeof(T) > sizeof(SubType), "SubType size is greater than type T");

	// condition for number n ;
	if (position > (sizeof(T) / sizeof(SubType)) + sizeof(SubType)  - 2) {
		std::cout << "\n check the number n\n";
		return {};
	}


	std::memcpy((char*)&value + position, &sub_value, sizeof(SubType));

	return value;
}
