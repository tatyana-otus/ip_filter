#include <algorithm>
#include <iterator>
#include "filter.h"


static std::ostream& operator << (std::ostream& os, const rec_t& m) 
{
    os << m[0] << '.' << m[1] << '.' << m[2] << '.' <<  m[3] << "\n";
    return os;
}

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
static auto split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }
    r.push_back(str.substr(start));

    return r;
}

std::vector<rec_t> get_data(std::istream& is)
{
    std::vector<rec_t> pool;

    for(std::string line; std::getline(is, line);){ 
        auto v = split(line, '\t'); 
        auto m = split(v.at(0), '.');
        if (m.size() == cn_bytes_in_ip) {     

            pool.push_back( {{ (ip_t)stoul(m[0]), (ip_t)stoul(m[1]), 
                               (ip_t)stoul(m[2]), (ip_t)stoul(m[3]) }} );
        }   
    }
    return pool;
}


void  process_data(std::ostream& os,  std::vector<rec_t>&& pool) {

    std::sort(pool.begin(), pool.end(), std::greater<rec_t>());

    std::for_each(pool.cbegin(), pool.cend(), [&os](const auto& ip) { os << ip; });

    std::for_each(pool.cbegin(), pool.cend(), [&os](const auto& ip) { if (f_and<rec_t, 0,1>(ip))
                                                                         os << ip; 
                                                                 });
    std::for_each(pool.cbegin(), pool.cend(), [&os](const auto& ip) { if (f_and<rec_t, 0,46, 1,70>(ip))
                                                                         os << ip; 
                                                                 });
    std::for_each(pool.cbegin(), pool.cend(), [&os](const auto& ip) { if (f_any<rec_t, 46>(ip))
                                                                         os << ip; 
                                                                 });
}