#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <cmath>

#include "lfu_cache.h"

bool TestLFUCache()
{
    size_t cache_hit_count = 0;

    int cache_capacity = 0;
    std::cin >> cache_capacity;

    LFUCache Cache(cache_capacity);

    int elems_count = 0;
    std::cin >> elems_count;

    int elem_key = 0;
    for (size_t i = 0; i < elems_count; i++)
    {
        std::cin >> elem_key;
        if (Cache.get(elem_key) != -1)
            cache_hit_count++;
        else
            Cache.put(elem_key, FICT_ELEM_VALUE);
    }

    std::cout << cache_hit_count << std::endl;

    return true;
}

int main(int argc, const char** argv)
{
    TestLFUCache();

    return 0;
}
