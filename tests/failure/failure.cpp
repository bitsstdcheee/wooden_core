#include <gtest/gtest.h>

TEST(FailureTest, BasicTest) {
    EXPECT_EQ(1, 1.01);
}