#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <cmath>

#include "lfu_cache.h"

size_t TestLFUCache(std::istream& input)
{
    size_t cache_hit_count = 0;

    int cache_capacity = 0;
    input >> cache_capacity;

    LFUCache Cache(cache_capacity);

    int elems_count = 0;
    input >> elems_count;

    int elem_key = 0;
    for (size_t i = 0; i < elems_count; i++)
    {
        input >> elem_key;
        if (Cache.get(elem_key) != -1)
            cache_hit_count++;
        else
            Cache.put(elem_key, FICT_ELEM_VALUE);
    }

    return cache_hit_count;
}

std::stringstream OpenFileAndReturnStrStream(std::string file_name)
{
    std::ifstream file(file_name);

    std::stringstream empty_ss("");

    if (!file) {
        std::cerr << "Could not open a test file!" << std::endl;
        return empty_ss;
    }

    std::string line = "";
    // if string stream not empty
    if (getline(file, line))
        return std::stringstream(line);

    return empty_ss;
}

#include <gtest/gtest.h>

TEST(TestLFUCacheCorrectness, Subtest_1) {
    std::stringstream ss = OpenFileAndReturnStrStream("../tests/test1.txt");
    ASSERT_FALSE(ss.str().empty());

    ASSERT_TRUE(TestLFUCache(ss) == 3);
}

TEST(TestLFUCacheCorrectness, Subtest_2) {
    std::stringstream ss = OpenFileAndReturnStrStream("../tests/test2.txt");
    ASSERT_FALSE(ss.str().empty());

    ASSERT_TRUE(TestLFUCache(ss) == 6);
}

TEST(TestLFUCacheCorrectness, Subtest_3) {
    std::stringstream ss = OpenFileAndReturnStrStream("../tests/test3.txt");
    ASSERT_FALSE(ss.str().empty());

    ASSERT_TRUE(TestLFUCache(ss) == 694);
}

TEST(TestLFUCacheCorrectness, Subtest_4) {
    std::stringstream ss = OpenFileAndReturnStrStream("../tests/test4.txt");
    ASSERT_FALSE(ss.str().empty());

    ASSERT_TRUE(TestLFUCache(ss) == 665463);
}

int main(int argc, char **argv)
{
    std::cout << TestLFUCache(std::cin) << std::endl;

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
