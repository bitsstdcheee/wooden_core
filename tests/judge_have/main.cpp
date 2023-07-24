#include <gtest/gtest.h>
#include <wooden_judge.h>

#include <utility>

using std::make_pair;
using namespace tskl;

#define make_weapon(x) make_pair(0, Skill(x, 1))

TEST(have_att_test, Positive) {
    EXPECT_EQ(have_att(make_weapon(tskl::wooden_sword)), true);
    EXPECT_EQ(have_att(make_weapon(tskl::yellow_sword)), true);
    EXPECT_EQ(have_att(make_weapon(tskl::stone_sword)), true);
    EXPECT_EQ(have_att(make_weapon(tskl::iron_sword)), true);
    EXPECT_EQ(have_att(make_weapon(tskl::gold_sword)), true);
    EXPECT_EQ(have_att(make_weapon(tskl::diamond_sword)), true);
    EXPECT_EQ(have_att(make_weapon(tskl::enchanted_sword)), true);
    EXPECT_EQ(have_att(make_weapon(tskl::bo_sword)), true);
    EXPECT_EQ(have_att(make_weapon(tskl::hither)), true);
    EXPECT_EQ(have_att(make_weapon(tskl::fist)), true);
    EXPECT_EQ(have_att(make_weapon(tskl::palm)), true);
    EXPECT_EQ(have_att(make_weapon(tskl::tube)), true);
    EXPECT_EQ(have_att(make_weapon(tskl::alpaca)), true);
    EXPECT_EQ(have_att(make_weapon(tskl::hither)), true);
}

TEST(have_att_test, Negative) {
    EXPECT_EQ(have_att(make_weapon(tskl::clap)), false);
    EXPECT_EQ(have_att(make_weapon(tskl::defense)), false);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}