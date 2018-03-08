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

#include "ip_rec.h"


std::ostream& operator << (std::ostream& os, const rec& ip) 
{
    for(auto ip_part = ip.rec_1.cbegin(); ip_part != ip.rec_1.cend(); ++ip_part) {
        if (ip_part != ip.rec_1.cbegin()){
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
        std::vector<rec>  ip_pool;

        for(std::string line; std::getline(std::cin, line);){ // generate !!!!!
            auto v = split(line, '\t');;  
            ip_pool.push_back( rec(split(v.at(0), '.')) ); 
        }

        std::sort (ip_pool.begin(), ip_pool.end());

        std::for_each(ip_pool.crbegin(), ip_pool.crend(), [](const rec& ip) { std::cout << ip; });

        std::for_each(ip_pool.crbegin(), ip_pool.crend(), [](const rec& ip) { if (filter<0,1>(ip)) std::cout << ip; });

        std::for_each(ip_pool.crbegin(), ip_pool.crend(), [](const rec& ip) { if (filter<0,46>(ip) && filter<1,70>(ip))
                                                                                  std::cout << ip; });

        std::for_each(ip_pool.crbegin(), ip_pool.crend(), [](const rec& ip) { if (filter<0,46>(ip) || filter<1,46>(ip) ||
                                                                                  filter<2,46>(ip) || filter<3,46>(ip) )
                                                                                  std::cout << ip; });

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
	
	return 0;
}