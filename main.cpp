#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <cmath>

#include "cache.h"

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

    std::cout << "LFU cache hit count:" << cache_hit_count << std::endl;

    return true;
}

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

    std::cout << "PCA cache hit count:" << cache_hit_count << std::endl;

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
        const int TEST_NUMBER = 3;
        const char* test_names[TEST_NUMBER] = {"../tests/easy_test.txt", "../tests/medium_test.txt", "../tests/hard_test.txt"};

        for(size_t i = 0; i < TEST_NUMBER; i++)
        {
            auto start = std::chrono::high_resolution_clock::now();
            TestLFUCache(test_names[i]);
            auto end = std::chrono::high_resolution_clock::now();

            std::chrono::duration<float> time_elapsed = end - start;
            std::cout << "LFU Cache time elapsed: " << time_elapsed.count() << std::endl;

            start = std::chrono::high_resolution_clock::now();
            TestPCACache(test_names[i]);
            end = std::chrono::high_resolution_clock::now();

            time_elapsed = end - start;
            std::cout << "PCA Cache time elapsed: " << time_elapsed.count() << std::endl;
        }
    }

    return 0;
}
