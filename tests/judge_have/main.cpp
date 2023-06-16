#include <gtest/gtest.h>
#include <utility>
#include <wooden_judge.h>

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

TEST(have_axe_test, Positive) {
    EXPECT_EQ(have_axe(make_weapon(tskl::wooden_axe)), true);
    EXPECT_EQ(have_axe(make_weapon(tskl::normal_axe)), true);
    EXPECT_EQ(have_axe(make_weapon(tskl::normal_axe)), true);
    EXPECT_EQ(have_axe(make_weapon(tskl::diamond_axe)), true);
    EXPECT_EQ(have_axe(make_weapon(tskl::enchanted_axe)), true);
}

TEST(have_axe_test, Negative) {
    EXPECT_EQ(have_axe(make_weapon(tskl::clap)), false);
    EXPECT_EQ(have_axe(make_weapon(tskl::defense)), false);
}

TEST(have_clap_axe_test, Positive) {
    EXPECT_EQ(have_clap_axe(make_weapon(tskl::wooden_axe)), true);
    EXPECT_EQ(have_clap_axe(make_weapon(tskl::normal_axe)), true);
    EXPECT_EQ(have_clap_axe(make_weapon(tskl::normal_axe)), true);
    EXPECT_EQ(have_clap_axe(make_weapon(tskl::diamond_axe)), true);
    EXPECT_EQ(have_clap_axe(make_weapon(tskl::enchanted_axe)), true);
    EXPECT_EQ(have_clap_axe(make_weapon(tskl::clap)), true);
}

TEST(have_clap_axe_test, Negative) {
    EXPECT_EQ(have_clap_axe(make_weapon(tskl::defense)), false);
    EXPECT_EQ(have_clap_axe(make_weapon(tskl::wooden_sword)), false);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}