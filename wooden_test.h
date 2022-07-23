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

#define enum2str(val) #val

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
inline const std::map<T1, T2> gen_map(const int player_num, const std::vector<T1> vec1, const std::vector<T2> vec2) {
    assert(vec1.size() == (long long unsigned int)player_num);
    assert(vec2.size() == (long long unsigned int)player_num);
    std::map<T1, T2> mp;
    mp.clear();
    for (int i = 0; i < player_num; i++) {
        mp[vec1[i]] = vec2[i];
    }
    return mp;
}

// gen_repeated_vec: 生成重复一个对象的 vec
template <typename T>
inline const std::vector<T> gen_repeated_vec(const T obj, const int times) {
    auto* vec = new std::vector<T>(times);
    // vector clear() 会导致 size 变为 0
    // vec->clear();
    for (int i = 0; i < times; i++) {
        (*vec)[i] = obj;
    }
    return *vec;
}

inline const std::vector<int> gen_default_player(const int player_num) {
    auto* vec = new std::vector<int>(player_num);
    // vec->clear();
    for (int i = 0; i < player_num; i++) {
        (*vec)[i] = i + 1;
    }
    return *vec;
} 

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

inline const std::map<int, int> gen_cleared_skl() {
    std::map<int, int> mp;
    mp.clear();
    for (int i = MIN_SKILL_NUM; i <= MAX_SKILL_NUM; i++) {
        mp[i] = 0;
    }
    return mp;
}

inline const std::map<int, bool> gen_all_alive(const std::vector<int>& players) {
    std::map<int, bool> mp;
    mp.clear();
    for (auto player : players) {
        mp[player] = false;
    }
    return mp;
}


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

    TESTN() {
        player_num = 0;
        players.clear();
        qi.clear();
        tag_died.clear();
        skl_count.clear();
        res_tag_died.clear();
        res_qi.clear();
    }

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
        std::string _comment = "") {
        player_num = _player_num;
        players = std::move(_players);
        qi = std::move(_qi);
        tag_died = std::move(_tag_died);
        skl_count = std::move(_skl_count);
        using_skill = std::move(_using_skill);
        target = std::move(_target);
        res_tag_died = std::move(_res_tag_died);
        res_qi = std::move(_res_qi);
        comment = std::move(_comment);
    }

    void info() const {
        std::cout << "comment:   " << comment << std::endl;
        std::cout << "player:    " << player_num << " persons" << std::endl;
        std::cout << "id:        ";
        for (int player : players) {
            std::cout << player << "\t";
        }
        std::cout << std::endl;
        std::cout << "died:      ";
        bool flag = false; // 标记是否输出过死亡玩家的 id
        for (int player : players) {
            if (tag_died.at(player) == false) std::cout << " ";
            else {
                std::cout << "*";
                flag = true;
            }
            std::cout << "\t";
        }
        if (flag == false) {
            std::cout << "\tEmpty!";
        } 
        std::cout << std::endl;
        std::cout << "skl_count: " << std::endl;
        for (int player: players) {
            flag = false;
            std::cout << "\tPlayer " << player << ": ";
            if (skl_count.at(player).empty()) {
                // 理论上来说不可能出现
                assert(skl_count.at(player).empty() == false);
                std::cout << "Empty" << std::endl;
                break;
            }
            for (auto i: skl_count.at(player)) {
                if (i.second == 0) continue;
                flag = true;
                std::cout << std::endl;
                std::cout << "\t\t- " << i.first << "\t: " << i.second << " time";
                if (i.second > 1) std::cout << "s";
                std::cout << std::endl;
            }
            if (flag == false) {
                std::cout << "Empty" << std::endl;
            }
        }
        std::cout << "skill:    " << std::endl;
        for (int player: players) {
            std::cout << "\tPlayer " << player << ": ";
            if (using_skill.at(player) == test::none) {
                std::cout << "None";
            }
            else {
                std::cout << using_skill.at(player) << " -> Player " << target.at(player);
            }
            std::cout << std::endl;
        }
        
    }
};

const TESTN test1 = TESTN(4,
    gen_default_player(4),
    gen_map<int, float>(4, gen_default_player(4), gen_repeated_vec<float>(0, 4)),
    gen_all_alive(gen_default_player(4)),
    gen_map<int, std::map<int, int>>(4, gen_default_player(4), gen_repeated_vec(gen_cleared_skl(), 4)),
    gen_map<int, test::skill>(4, gen_default_player(4), {test::clap, test::none, test::clap, test::none}),
    gen_map<int, int>(4, gen_default_player(4), gen_repeated_vec(0, 4)),
    gen_map<int, bool>(4, gen_default_player(4), gen_repeated_vec(false, 4)),
    gen_map<int, float>(4, gen_default_player(4), {1, 0, 1, 0}),
    "纯拍气");

const TESTN test2 = TESTN(4, 
    gen_default_player(4), 
    gen_map<int, float>(4, gen_default_player(4), gen_repeated_vec<float>(0, 4)), 
    gen_all_alive(gen_default_player(4)), 
    gen_map<int, std::map<int, int>>(4, gen_default_player(4), gen_repeated_vec(gen_cleared_skl(), 4)), 
    gen_map<int, test::skill>(4, gen_default_player(4), gen_repeated_vec(test::none, 4)), 
    gen_map<int, int>(4, gen_default_player(4), gen_repeated_vec(0, 4)), 
    gen_map<int, bool>(4, gen_default_player(4), gen_repeated_vec(false, 4)), 
    gen_map<int, float>(4, gen_default_player(4), gen_repeated_vec<float>(0, 4)), 
    "Null 局");

const TESTN test3 = TESTN(4, 
    gen_default_player(4),
    gen_map<int, float>(4, gen_default_player(4), {2, 3, 6, 3}),
    gen_all_alive(gen_default_player(4)),
    gen_map<int, std::map<int, int>>(4, gen_default_player(4), gen_repeated_vec(gen_cleared_skl(), 4)),
    gen_map<int, test::skill>(4, gen_default_player(4), {test::wooden_axe, test::normal_axe, test::enchanted_axe, test::enchanted_axe}),
    gen_map<int, int>(4, gen_default_player(4), gen_repeated_vec(0, 4)),
    gen_map<int, bool>(4, gen_default_player(4), {false, false, false, true}),
    gen_map<int, float>(4, gen_default_player(4), {4, 5, 12, 0}),
    "镐局 1");

const TESTN test4 = TESTN(2,
    gen_default_player(2),
    gen_map<int, float>(2, gen_default_player(2), {1, 0}),
    gen_all_alive(gen_default_player(2)),
    gen_map<int, std::map<int, int>>(2, gen_default_player(2), gen_repeated_vec(gen_cleared_skl(), 2)),
    gen_map<int, test::skill>(2, gen_default_player(2), {test::wooden_axe, test::clap}),
    gen_map<int, int>(2, gen_default_player(2), gen_repeated_vec(0, 2)),
    gen_map<int, bool>(2, gen_default_player(2), {true, false}),
    gen_map<int, float>(2, gen_default_player(2), {0, 1}),
    "镐局 2");

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

#endif