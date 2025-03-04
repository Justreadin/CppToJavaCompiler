#include <gtest/gtest.h>

// A simple test case
TEST(SampleTest, BasicAssertions) {
    EXPECT_EQ(1 + 1, 2);
}

// The main function to run all tests
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
