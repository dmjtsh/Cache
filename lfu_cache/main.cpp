#include <iostream>

#include "test_interface.h"
#include "lfu_cache.h"

int main(int argc, char **argv)
{
    std::cout << CountLFUCacheHitFromInput(std::cin) << std::endl;

    return 0;
}
