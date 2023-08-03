#ifndef WOODEN_SKILL_CPP
#define WOODEN_SKILL_CPP
#include "wooden_skill.h"

#include <array>

const int tskl::MIN_SKILL_NUM = 0;
const int tskl::MAX_SKILL_NUM = 30;

// clang-format off
const std::array<std::string, tskl::MAX_SKILL_NUM + 1> skill_name = { u8"空",
    u8"拍气", u8"木镐", u8"镐子", u8"钻镐", u8"附魔钻镐",
    u8"木剑", u8"黄剑", u8"石剑", u8"铁剑", u8"金剑",
    u8"钻剑", u8"附魔钻剑", u8"普防", u8"中防", u8"大防",
    u8"阿西巴", u8"zd", u8"Hither", u8"拳", u8"掌",
    u8"波波剑", u8"羊驼", u8"管", u8"咕噜咕噜", u8"评测",
    u8"夹拳", u8"夹剑", u8"夹波波剑", u8"空手", u8"黄剑 (毁坏)"
};
// clang-format on

string tskl::query_skill_overlay_name(skill skl) {
    if (skl == wooden_sword || skl == fist || skl == stone_sword ||
        skl == iron_sword || skl == gold_sword || skl == diamond_sword ||
        skl == enchanted_sword) {
        return "WF";
    }
    if (skl == palm) return "palm_group";
    if (skl == bo_sword) return "bo_group";
    if (skl == tube) return "tube_group";
    if (skl == alpaca) return "alpaca_group";

    if (skl == wooden_axe) return "wooden_axe_group";
    if (skl == normal_axe) return "normal_axe_group";
    if (skl == diamond_axe) return "diamond_axe_group";
    if (skl == enchanted_axe) return "enchanted_axe_group";

    if (skl == hands) return "hands_group";

    return "none";
}

bool tskl::query_skill_can_overlay(skill skl) {
    return query_skill_overlay_name(skl) != "none";
}

bool tskl::query_skill_is_attack(skill skl) {
    return skl == wooden_sword || skl == stone_sword || skl == iron_sword ||
           skl == gold_sword || skl == diamond_sword ||
           skl == enchanted_sword || skl == yellow_sword || skl == fist ||
           skl == palm || skl == bo_sword || skl == tube || skl == alpaca ||
           skl == hither;
}

bool tskl::query_skill_is_defense(skill skl) {
    return skl == defense || skl == mid_defense || skl == large_defense ||
           skl == hands || skl == ashiba || skl == zd;
}

std::string tskl::get_skill_name(const int& skl) { return skill_name[skl]; }

std::string tskl::get_skill_name(const skill& skl) { return skill_name[skl]; }
#endif  // WOODEN_SKILL_CPP