#pragma once

template<typename T1, typename T2>
constexpr bool greaterSize(const T1& o1, const T2& o2) {
	return sizeof(T1) > sizeof(T2);
}

template<typename T1, typename T2>
constexpr bool equalSize(const T1& o1, const T2& o2) {
	return sizeof(T1) == sizeof(T2);
}

template<typename T1, typename T2>
constexpr bool lessSize(const T1& o1, const T2& o2) {
	return sizeof(o1) < sizeof(o2);
}

template<typename T>
constexpr size_t Sizeof(const T& obj) {
	return sizeof(obj);
}

template<typename T1, typename T2, typename MesureFunction >
constexpr bool compareSize(const T1& o1, const T2& o2) {
	return true;
}

template<typename T>
constexpr size_t SizeOf() {
	return sizeof(T);
}

template<typename T>
 struct Size_Of
{
   	enum { size = sizeof(T) };

	constexpr size_t operator ()(void) const noexcept { return sizeof(T); }

};