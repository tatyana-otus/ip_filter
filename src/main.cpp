#include <iostream>
#include <algorithm>
#include <iterator>

#include "filter.h"

std::ostream& operator << (std::ostream& os, const rec_t& m) 
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
auto split(const std::string &str, char d)
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


int main () 
{
    try
    {
        std::vector<rec_t> ip_pool;

        for(std::string line; std::getline(std::cin, line);){ 
            auto v = split(line, '\t');;  
            auto m = split(v.at(0), '.');
            if (m.size() == cn_bytes_in_ip) {
                ip_pool.push_back( {{ (ip_t)stoul(m[0]), (ip_t)stoul(m[1]), 
                                      (ip_t)stoul(m[2]), (ip_t)stoul(m[3]) }} );
            }   
        }
        
        std::sort(ip_pool.begin(), ip_pool.end());

        std::for_each(ip_pool.crbegin(), ip_pool.crend(), [](const auto& ip) { std::cout << ip; });

        std::for_each(ip_pool.crbegin(), ip_pool.crend(), [](const auto& ip) { if (filter<0,1>(ip))
                                                                                   std::cout << ip; 
                                                                             });

        std::for_each(ip_pool.crbegin(), ip_pool.crend(), [](const auto& ip) { if (filter<0,46>(ip) && filter<1,70>(ip))  
                                                                                    std::cout << ip; 
                                                                             });
        std::for_each(ip_pool.crbegin(), ip_pool.crend(), [](const auto& ip) { if (filter_any<46>(ip))  
                                                                                    std::cout << ip; 
                                                                             });

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}