#include <gtest/gtest.h>
#include <utility>
#include "../../wooden_judge.cpp"

using std::make_pair;

#define make_weapon(x) make_pair(0, Skill(x, 1))

TEST(FirstTest, BasicAssertions) {
    EXPECT_EQ(-1, 1);
}

TEST(have_att_test, BasicAssertions) {
    EXPECT_TRUE(have_att(make_weapon(tskl::wooden_sword)));
    EXPECT_TRUE(have_att(make_pair(0, Skill(tskl::yellow_sword, 1))));
    EXPECT_TRUE(have_att(make_pair(0, Skill(tskl::stone_sword, 1))));
    EXPECT_TRUE(have_att(make_pair(0, Skill(tskl::iron_sword, 1))));
    EXPECT_TRUE(have_att(make_pair(0, Skill(tskl::gold_sword, 1))));
    EXPECT_TRUE(have_att(make_pair(0, Skill(tskl::diamond_sword, 1))));
    EXPECT_TRUE(have_att(make_pair(0, Skill(tskl::enchanted_sword, 1))));
}