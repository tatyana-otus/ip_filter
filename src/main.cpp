#include "filter.h"

int main () 
{
    try
    {
        process_data(std::cout, get_data(std::cin));

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}