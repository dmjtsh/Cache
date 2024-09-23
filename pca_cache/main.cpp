#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <cmath>

#include "pca_cache.h"

bool TestPCACache(std::string test_name)
{
    std::ifstream file(test_name);

    size_t cache_hit_count = 0;

    if (!file) {
        std::cerr << "Could not open a test file!" << std::endl;
        return false;
    }

    std::string line = "";
    if (getline(file, line)) {
        // Using stringstream to chunk a test string
        std::stringstream ss(line);

        int cache_capacity = 0;
        ss >> cache_capacity;

        PCACache PCACache(cache_capacity);

        int elems_count = 0;
        ss >> elems_count;

        int* elems_array = new int[elems_count];
        int elems_key = 0;
        for (size_t i = 0; i < elems_count; i++)
        {
            ss >> elems_key;
            *(elems_array+i) = elems_key;
        }

        cache_hit_count = PCACache.countCacheHit(elems_count, elems_array);

        delete[] elems_array;
    }

    file.close();

    std::cout << cache_hit_count << std::endl;

    return true;
}

int main(int argc, const char** argv)
{
    if (argc > 1)
    {
        for(size_t i = 1; i < argc; i++)
            TestPCACache((std::string)(argv[i]));
    }
    else
    {
        TestPCACache("../../hard_test.txt");
    }

    return 0;
}
