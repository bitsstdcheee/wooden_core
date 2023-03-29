#ifndef WOODEN_SKILL
#define WOODEN_SKILL
namespace tskl {
    enum skill {
        none = 0,  // 无

        clap = 1,  // 拍气

        wooden_axe = 2,   // 木镐 1->3 0    // 换气数 自带防御数
        normal_axe = 3,   // 镐子 2->4 0.5
        diamond_axe = 4,  // 钻镐 3->6 1
        enchanted_axe = 5,  // 附魔钻镐 6->12 2.5

        wooden_sword = 6,  // 木剑 1 1     // 气数 攻击数
        yellow_sword = 7,  // 黄剑 1 2.5 特殊判定
        stone_sword = 8,   // 石剑 2 2
        iron_sword = 9,    // 铁剑 3 3
        gold_sword = 10,   // 金剑 4 4
        diamond_sword = 11, // 钻剑 5 5
        enchanted_sword = 12, // 附魔钻剑 6 6

        defense = 13,  // 普防 0~3
        mid_defense = 14, // 中防 1~5
        large_defense = 15, // 大防 1~6
        ashiba = 16, // 阿西巴 0~5 每小局 2 次
        zd = 17, // zd 0~无限 每小局 1 次

        hither = 18 // Hither 全场 1 攻 每小局 1 次
    };
}
#endif
