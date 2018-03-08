
#include <iostream>
#include <sys/time.h>
#include <chrono>
#include <thread>
#include <cassert>
#include <cstdlib>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <assert.h>

template<int idx, int value>
inline bool filter(const std::vector<std::string>& r) {

    static_assert(idx < 4, "");
    static_assert(value <= 255, "");
    static_assert(value >=   0, "");

    return (stoul(r.at(idx)) == value);
}