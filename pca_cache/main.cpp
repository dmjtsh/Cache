#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <cmath>

#include "pca_cache.h"

size_t TestPCACache(std::istream& input)
{
    int cache_capacity = 0;
    input >> cache_capacity;

    PCACache PCACache(cache_capacity);

    int elems_count = 0;
    input >> elems_count;

    int* elems_array = new int[elems_count];
    int elems_key = 0;
    for (size_t i = 0; i < elems_count; i++)
    {
        input >> elems_key;
        *(elems_array+i) = elems_key;
    }

    size_t cache_hit_count = PCACache.countCacheHit(elems_count, elems_array);

    delete[] elems_array;

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

TEST(TestPCACacheCorrectness, Subtest_1) {
    std::stringstream ss = OpenFileAndReturnStrStream("../tests/test1.txt");
    ASSERT_FALSE(ss.str().empty());

    ASSERT_TRUE(TestPCACache(ss) == 3);
}

TEST(TestPCACacheCorrectness, Subtest_2) {
    std::stringstream ss = OpenFileAndReturnStrStream("../tests/test2.txt");
    ASSERT_FALSE(ss.str().empty());

    ASSERT_TRUE(TestPCACache(ss) == 7);
}

TEST(TestPCACacheCorrectness, Subtest_3) {
    std::stringstream ss = OpenFileAndReturnStrStream("../tests/test3.txt");
    ASSERT_FALSE(ss.str().empty());

    ASSERT_TRUE(TestPCACache(ss) == 857);
}

TEST(TestPCACacheCorrectness, Subtest_4) {
    std::stringstream ss = OpenFileAndReturnStrStream("../tests/test4.txt");
    ASSERT_FALSE(ss.str().empty());

    ASSERT_TRUE(TestPCACache(ss) == 894836);
}

int main(int argc, char **argv)
{
    std::cout << TestPCACache(std::cin) << std::endl;

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
