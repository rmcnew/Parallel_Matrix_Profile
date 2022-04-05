#include <gtest/gtest.h>

TEST(HelloTest, Demo) {
    
    EXPECT_STRNE("hello", "world");

    EXPECT_EQ(7*6, 42);
}

