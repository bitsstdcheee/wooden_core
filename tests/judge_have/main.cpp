#include <gtest/gtest.h>
#include <utility>
#include <wooden_judge.h>

using std::make_pair;
using namespace tskl;

#define make_weapon(x) make_pair(0, Skill(x, 1))

TEST(have_att_test, Positive) {
    EXPECT_TRUE(have_att(make_weapon(tskl::wooden_sword)));
    EXPECT_TRUE(have_att(make_weapon(tskl::yellow_sword)));
    EXPECT_TRUE(have_att(make_weapon(tskl::stone_sword)));
    EXPECT_TRUE(have_att(make_weapon(tskl::iron_sword)));
    EXPECT_TRUE(have_att(make_weapon(tskl::gold_sword)));
    EXPECT_TRUE(have_att(make_weapon(tskl::diamond_sword)));
    EXPECT_TRUE(have_att(make_weapon(tskl::enchanted_sword)));
    EXPECT_TRUE(have_att(make_weapon(tskl::bo_sword)));
    EXPECT_TRUE(have_att(make_weapon(tskl::hither)));
    EXPECT_TRUE(have_att(make_weapon(tskl::fist)));
    EXPECT_TRUE(have_att(make_weapon(tskl::palm)));
    EXPECT_TRUE(have_att(make_weapon(tskl::tube)));
    EXPECT_TRUE(have_att(make_weapon(tskl::alpaca)));
    EXPECT_TRUE(have_att(make_weapon(tskl::hither)));
}

TEST(have_att_test, Negative) {
    EXPECT_FALSE(have_att(make_weapon(tskl::clap)));
    EXPECT_FALSE(have_att(make_weapon(tskl::defense)));
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}