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

//#include "ip_rec.h"
#include "filter.h"


std::ostream& operator << (std::ostream& os, const std::vector<std::string>& ip) 
{
    for(auto ip_part = ip.cbegin(); ip_part != ip.cend(); ++ip_part) {
        if (ip_part != ip.cbegin()){
            os << ".";
        }
        os << *ip_part;
     }
    os << "\n";
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

        std::multimap<uint32_t, std::vector<std::string>> ip_pool;
 

        for(std::string line; std::getline(std::cin, line);){ // generate !!!!!
            auto v = split(line, '\t');;  
            auto m = split(v.at(0), '.');
            uint32_t  idx = (stoul(m[0]) << 24) | (stoul(m[1]) << 16) | (stoul(m[2]) << 8) | stoul(m[3]);

            ip_pool.insert ( std::pair<uint32_t, std::vector<std::string>>(idx, m) );

        }

        std::for_each(ip_pool.crbegin(), ip_pool.crend(), [](const auto& ip) { std::cout << ip.second; });

        std::for_each(ip_pool.crbegin(), ip_pool.crend(), [](const auto& ip) { if (filter<0,1>(ip.second)) std::cout << ip.second; });

        std::for_each(ip_pool.crbegin(), ip_pool.crend(), [](const auto& ip) { if (filter<0,46>(ip.second) && filter<1,70>(ip.second))
                                                                                  std::cout << ip.second; });

        std::for_each(ip_pool.crbegin(), ip_pool.crend(), [](const auto& ip) { if (filter<0,46>(ip.second) || filter<1,46>(ip.second) ||
                                                                                  filter<2,46>(ip.second) || filter<3,46>(ip.second) )
                                                                                  std::cout << ip.second; });

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
	
	return 0;
}