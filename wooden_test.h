#ifndef WOODEN_TEST_H
#define WOODEN_TEST_H

#include <array>
#include <initializer_list>
#include <map>
#include <string>
#include <utility>
#include <vector>
#include <iostream>
#include <cassert>

#include "wooden_macro.h"

// #define debug

const int MIN_SKILL_NUM = 0;
const int MAX_SKILL_NUM = 17;

namespace test {
    using skill = enum {
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
    };
}

// gen_vector: 生成 vector 形式
/* 本函数形式被删除, 原因是 initializer_list 可以隐式转换为 vector, 以适配 vector 容器类型
template <typename T>
inline const std::vector<T> gen_vector(const int player_num, const std::initializer_list<T> list) {
    assert(list.size() == player_num);
    int cnt = 0;
    auto* vec = new std::vector<T>(player_num);
    for (auto i: list) {
        (*vec)[cnt++] = i;
    }
    return (*vec);
}
*/


// gen_map: 生成 map 形式
/* 本函数形式被删除, 原因是 initializer_list 可以隐式转换为 vector, 以适配 vector 容器类型
template <typename T1, typename T2>
inline const std::map<T1, T2> gen_map(const int player_num, const std::initializer_list<T1> list1, std::initializer_list<T2> list2) {
    assert(list1.size() == player_num);
    assert(list2.size() == player_num);
    std::map<T1, T2> mp;
    mp.clear();
    auto a1 = list1.begin();
    auto a2 = list2.begin();
    for (;
        a1 != list1.end() && a2 != list2.end();
        a1++, a2++
    ) {
        mp[(*a1)] = (*a2);
    }
    return mp;
}
*/

// gen_map: 生成 map 形式
template <typename T1, typename T2>
const std::map<T1, T2> gen_map(const int player_num, const std::vector<T1> vec1, const std::vector<T2> vec2);

// gen_repeated_vec: 生成重复一个对象的 vec
template <typename T>
const std::vector<T> gen_repeated_vec(const T obj, const int times);

const std::vector<int> gen_default_player(const int);

/*
// gen_qi: 生成带 float 的 map 形式
template <typename T1>
inline const std::map<T1, float> gen_qi(const int player_num, const std::initializer_list<T1> list1, std::initializer_list<float> list2) {
    assert(list1.size() == player_num);
    assert(list2.size() == player_num);
    std::map<T1, float> mp;
    mp.clear();
    auto a1 = list1.begin();
    auto a2 = list2.begin();
    for (;
        a1 != list1.end() && a2 != list2.begin();
        a1++, a2++
    ) {
        mp[(*a1)] = (*a2);
    }
    return mp;
}
*/

const std::map<int, int> gen_cleared_skl();

const std::map<int, bool> gen_all_alive(const std::vector<int>&);


// TESTN: 打包测试样例的结构
struct TESTN {
    int player_num;  // 测试中的玩家个数
    std::vector<int> players;  // 测试初始的玩家 id
    std::map<int, float> qi;  // 测试初始的气数列表
    std::map<int, bool> tag_died;  // 测试初始的玩家死亡信息
    std::map<int, std::map<int, int>> skl_count;  // 测试初始值的招术使用情况
    std::map<int, test::skill> using_skill;  // 测试小局中玩家的出招
    std::map<int, int> target;  // 测试小局中玩家出招的对手
    std::map<int, bool> res_tag_died;  // 测试期望的玩家死亡信息
    std::map<int, float> res_qi;  // 测试期望的气数列表

    std::string comment;  // 备注

    TESTN();

    // TESTN: 玩家人数, 玩家id, 气数, 死亡标记, 招术计数器, 期望死亡标记, 期望气数, 备注
    TESTN(int _player_num,
        std::vector<int> _players,
        std::map<int, float> _qi,
        std::map<int, bool> _tag_died,
        std::map<int, std::map<int, int>> _skl_count,
        std::map<int, test::skill> _using_skill,
        std::map<int, int> _target,
        std::map<int, bool> _res_tag_died,
        std::map<int, float> _res_qi,
        std::string _comment);

    void info() const;
};


// const TESTN test3 = TESTN()

#ifdef ASSERT_TEST1
void do_test1_assert() {
    // tag_died
    assert(test1.tag_died.at(1) == false);
    assert(test1.tag_died.at(2) == false);
    assert(test1.tag_died.at(3) == false);
    assert(test1.tag_died.at(4) == false);
}
#endif

extern const TESTN test1;
extern const TESTN test2;
extern const TESTN test3;
extern const TESTN test4;
extern const TESTN test5;
extern const TESTN test6;
extern const TESTN test7;
extern const TESTN test8;
extern const TESTN test9;
extern const TESTN test10;
#endif