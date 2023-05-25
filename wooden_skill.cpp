#include "wooden_skill.h"

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