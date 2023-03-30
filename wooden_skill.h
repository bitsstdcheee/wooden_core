#ifndef WOODEN_SKILL
#define WOODEN_SKILL
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
        hither = 18


    };
}
#endif