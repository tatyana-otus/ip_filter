#include <iostream>
#include <map>
#include <algorithm>
#include <iterator>
#include "filter.h"



std::ostream& operator << (std::ostream& os, const rec_t& ip) 
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

        std::multimap<uint32_t, rec_t> ip_pool;
 

        for(std::string line; std::getline(std::cin, line);){ 
            auto v = split(line, '\t');;  
            auto m = split(v.at(0), '.');
            uint32_t  idx = (stoul(m[0]) << 24) | (stoul(m[1]) << 16) | (stoul(m[2]) << 8) | stoul(m[3]);

            ip_pool.insert ( std::pair<uint32_t, rec_t>(idx, m) );

        }

        std::for_each(ip_pool.crbegin(), ip_pool.crend(), [](const auto& ip) { std::cout << ip.second; });

        std::for_each(ip_pool.crbegin(), ip_pool.crend(), [](const auto& ip) { if (f_and<crec_t, 0,1>(ip.second))          std::cout << ip.second; });
        std::for_each(ip_pool.crbegin(), ip_pool.crend(), [](const auto& ip) { if (f_and<crec_t, 0,46, 1, 70>(ip.second))  std::cout << ip.second; });
        std::for_each(ip_pool.crbegin(), ip_pool.crend(), [](const auto& ip) { if (f_any<crec_t, 46>(ip.second))           std::cout << ip.second; });


    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }
	
	return 0;
}