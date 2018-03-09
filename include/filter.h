#pragma once

#include <string>
#include <vector>

using rec_t = std::vector<std::string>;
using crec_t = const rec_t&;




//-------------------------
template <typename T>
inline bool f_and(T r)
{
	return true;
}

template <typename T, int idx, int value, int ... args>
inline bool f_and(T r)
{
	static_assert(idx < 4, "");
    static_assert(value <= 255, "");
    static_assert(value >=   0, "");

	return ((stoul(r[idx]) == value) && f_and<T, args ...>(r));
}

//-------------------------

template <typename T>
inline bool f_or(T r)
{
	return false;
}

template <typename T, int idx, int value, int ... args>
inline bool f_or(T r)
{
	static_assert(idx < 4, "");
    static_assert(value <= 255, "");
    static_assert(value >=   0, "");

	return ((stoul(r[idx]) == value) || f_or<T, args ...>(r));
}

//-------------------------

template <typename T,  int value>
inline bool f_any(T r) 
{
	return f_or<T, 0, value, 1, value, 2, value, 3, value>(r);
}
