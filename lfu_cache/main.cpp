#include <iostream>

#include "test_interface.hpp"
#include "lfu_cache.hpp"

int main(int argc, char **argv)
{
    std::cout << CountLFUCacheHitFromInput(std::cin) << std::endl;

    return 0;
}
