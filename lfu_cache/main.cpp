#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <cmath>

#include "lfu_cache.h"

bool TestLFUCache(std::string test_name)
{
    std::ifstream file(test_name);

    if (!file) {
        std::cerr << "Could not open a test file!" << std::endl;
        return false;
    }

    size_t cache_hit_count = 0;

    std::string line = "";
    if (getline(file, line)) {
        // Using stringstream to chunk a test string
        std::stringstream ss(line);

        int cache_capacity = 0;
        ss >> cache_capacity;

        LFUCache Cache(cache_capacity);

        int elems_count = 0;
        ss >> elems_count;

        int elem_key = 0;
        for (size_t i = 0; i < elems_count; i++)
        {
            ss >> elem_key;
            if (Cache.get(elem_key) != -1)
                cache_hit_count++;
            else
                Cache.put(elem_key, FICT_ELEM_VALUE);
        }
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
            TestLFUCache((std::string)(argv[i]));
    }
    else
    {
        TestLFUCache("../../tests/hard_test.txt");
    }

    return 0;
}