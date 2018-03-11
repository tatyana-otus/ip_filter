#pragma once

#include <string>
#include <vector>
#include <array>
#include <bitset>

using ip_t =  uint32_t;

static const auto cn_bytes_in_ip = 4;

using rec_t = std::array<ip_t, cn_bytes_in_ip>;


template<int idx, int value>
inline bool filter(const rec_t& r) {

    static_assert(idx < 4, "");
    static_assert(value <= 255, "");
    static_assert(value >=   0, "");

    return (r[idx] == value);
} 

template <int value>
inline bool filter_any(const rec_t& r) 
{
    return (filter<0, value>(r) || filter<1, value>(r) ||
            filter<2, value>(r) || filter<3, value>(r));
}
