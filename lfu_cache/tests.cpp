#include <string>
#include <fstream>
#include <sstream>
#include <chrono>
#include <cmath>

#include <gtest/gtest.h>

#include "test_interface.h"

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

TEST(TestLFUCacheCorrectness, Subtest_1) {
    std::stringstream ss = OpenFileAndReturnStrStream("../tests/test1.txt");
    ASSERT_FALSE(ss.str().empty());

    ASSERT_TRUE(CountLFUCacheHitFromInput(ss) == 3);
}

TEST(TestLFUCacheCorrectness, Subtest_2) {
    std::stringstream ss = OpenFileAndReturnStrStream("../tests/test2.txt");
    ASSERT_FALSE(ss.str().empty());

    ASSERT_TRUE(CountLFUCacheHitFromInput(ss) == 6);
}

TEST(TestLFUCacheCorrectness, Subtest_3) {
    std::stringstream ss = OpenFileAndReturnStrStream("../tests/test3.txt");
    ASSERT_FALSE(ss.str().empty());

    ASSERT_TRUE(CountLFUCacheHitFromInput(ss) == 694);
}

TEST(TestLFUCacheCorrectness, Subtest_4) {
    std::stringstream ss = OpenFileAndReturnStrStream("../tests/test4.txt");
    ASSERT_FALSE(ss.str().empty());

    ASSERT_TRUE(CountLFUCacheHitFromInput(ss) == 665463);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
