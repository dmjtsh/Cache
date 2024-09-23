#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <cmath>

#include "pca_cache.h"

bool TestPCACache()
{

    int cache_capacity = 0;
    std::cin >> cache_capacity;

    PCACache PCACache(cache_capacity);

    int elems_count = 0;
    std::cin >> elems_count;

    int* elems_array = new int[elems_count];
    int elems_key = 0;
    for (size_t i = 0; i < elems_count; i++)
    {
        std::cin >> elems_key;
        *(elems_array+i) = elems_key;
    }

    size_t cache_hit_count = PCACache.countCacheHit(elems_count, elems_array);

    delete[] elems_array;

    std::cout << cache_hit_count << std::endl;

    return true;
}

int main(int argc, const char** argv)
{
    TestPCACache();

    return 0;
}
