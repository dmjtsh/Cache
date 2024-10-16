#include "test_interface.hpp"

#include <gtest/gtest.h>

#include <fstream>
#include <sstream>

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


TEST(TestPCACacheCorrectness, Subtest_1) {
    std::stringstream ss = OpenFileAndReturnStrStream("../tests/test1.txt");
    ASSERT_FALSE(ss.str().empty());

    ASSERT_TRUE(CountPCACacheHitFromInput(ss) == 3);
}

TEST(TestPCACacheCorrectness, Subtest_2) {
    std::stringstream ss = OpenFileAndReturnStrStream("../tests/test2.txt");
    ASSERT_FALSE(ss.str().empty());

    ASSERT_TRUE(CountPCACacheHitFromInput(ss) == 7);
}

TEST(TestPCACacheCorrectness, Subtest_3) {
    std::stringstream ss = OpenFileAndReturnStrStream("../tests/test3.txt");
    ASSERT_FALSE(ss.str().empty());

    ASSERT_TRUE(CountPCACacheHitFromInput(ss) == 857);
}

TEST(TestPCACacheCorrectness, Subtest_4) {
    std::stringstream ss = OpenFileAndReturnStrStream("../tests/test4.txt");
    ASSERT_FALSE(ss.str().empty());

    ASSERT_TRUE(CountPCACacheHitFromInput(ss) == 894836);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
