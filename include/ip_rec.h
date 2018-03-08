#pragma once

#include <iostream>
#include <sys/time.h>
#include <chrono>
#include <thread>
#include <cassert>
#include <cstdlib>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <assert.h>

using ip_rec = std::vector<std::string>;

struct rec {
    rec(ip_rec _rec_1);

    ip_rec rec_1;

    bool operator< (const rec& rec_2) const;

    size_t size() ;
};

template<int idx, int value>
inline bool filter(const rec& r) {

	static_assert(idx < 4, "");
	static_assert(value <= 255, "");
	static_assert(value >=   0, "");

	return (stoul(r.rec_1.at(idx)) == value);
}