#ifndef WOODEN_SKILL_H
#define WOODEN_SKILL_H
#include <string>
using std::string;
namespace tskl {
enum skill {
    // 无
    none = 0,

    // 拍气
    clap = 1,

    // 木镐 1->3 0    // 换气数 自带防御数
    wooden_axe = 2,

    // 镐子 2->4 0.5
    normal_axe = 3,

    // 钻镐 3->6 1
    diamond_axe = 4,

    // 附魔钻镐 6->12 2.5
    enchanted_axe = 5,

    // 木剑 1 1     // 气数 攻击数
    wooden_sword = 6,

    // 黄剑 1 2.5 特殊判定
    yellow_sword = 7,

    // 石剑 2 2
    stone_sword = 8,

    // 铁剑 3 3
    iron_sword = 9,

    // 金剑 4 4
    gold_sword = 10,

    // 钻剑 5 5
    diamond_sword = 11,

    // 附魔钻剑 6 6
    enchanted_sword = 12,

    // 普防 0~3
    defense = 13,

    // 中防 1~5
    mid_defense = 14,

    // 大防 1~6
    large_defense = 15,

    // 阿西巴 0~5 每小局 2 次
    ashiba = 16,

    // zd 0~无限 每小局 1 次
    zd = 17,

    // Hither 全场 1 攻 每小局 1 次
    hither = 18,

    // 拳
    fist = 19,

    // 掌
    palm = 20,

    // 波波剑
    bo_sword = 21,

    // 羊驼
    alpaca = 22,

    // 管
    tube = 23,

    // gulu
    gulu = 24,

    // 评测
    judge = 25,

    // 夹拳
    fetch_fist = 26,

    // 夹剑
    fetch_sword = 27,

    // 夹波波剑
    fetch_bo = 28,

    // 空手
    hands = 29,
};

extern const int MIN_SKILL_NUM;
extern const int MAX_SKILL_NUM;

// 获取招式对应的叠加组 id
string query_skill_overlay_name(skill);

// 查询招式是否可以叠加
bool query_skill_can_overlay(skill);

// 查询该招式是否为攻击招式: sword, fist, palm, bo_sword, tube, alpaca, hither.
bool query_skill_is_attack(skill);

// 查询该招式是否为防御招式: defense, mid_defense, large_defense, hands, ashiba,
// zd.
bool query_skill_is_defense(skill);
}  // namespace tskl
#endif  // WOODEN_SKILL_H
