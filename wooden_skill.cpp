#ifndef WOODEN_SKILL_CPP
#define WOODEN_SKILL_CPP
#include "wooden_skill.h"

#include <array>

const int tskl::MIN_SKILL_NUM = 0;
const int tskl::MAX_SKILL_NUM = 31;

// clang-format off
const std::array<std::string, tskl::MAX_SKILL_NUM + 1> skill_name = { "空",
    "拍气", "木镐", "镐子", "钻镐", "附魔钻镐",
    "木剑", "黄剑", "石剑", "铁剑", "金剑",
    "钻剑", "附魔钻剑", "普防", "中防", "大防",
    "阿西巴", "zd", "Hither", "拳", "掌",
    "波波剑", "羊驼", "管", "咕噜咕噜", "评测",
    "夹拳", "夹剑", "夹波波剑", "空手", "黄剑 (毁坏)",
    "管(选)"
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
    if (skl == tube || skl == tube_selected) return "tube_group";
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
           skl == hither || skl == tube_selected;
}

bool tskl::query_skill_is_defense(skill skl) {
    return skl == defense || skl == mid_defense || skl == large_defense ||
           skl == hands || skl == ashiba || skl == zd;
}

std::string tskl::get_skill_name(const skill& skl) { return skill_name[skl]; }
#endif  // WOODEN_SKILL_CPP