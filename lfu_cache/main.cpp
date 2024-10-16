#include "test_interface.hpp"
#include "lfu_cache.hpp"

#include <iostream>

int main(int argc, char **argv)
{
    try
    {
        size_t cache_hit_count = CountLFUCacheHitFromInput(std::cin);
        std::cout << "Cache hit count: " << cache_hit_count << std::endl;
    }

    catch (const std::invalid_argument& e)
    {
        std::cerr << "Input error: " << e.what() << std::endl;
    }
    catch (const std::out_of_range& e)
    {
        std::cerr << "Input error: " << e.what() << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
    }

    return 0;
}
