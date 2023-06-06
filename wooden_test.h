#ifndef WOODEN_TEST_H
#define WOODEN_TEST_H

#include <array>
#include <cassert>
#include <initializer_list>
#include <iostream>
#include <map>
#include <new>
#include <string>
#include <utility>
#include <vector>

#include "wooden_debug.h"
#include "wooden_judge.h"
#include "wooden_macro.h"
#include "wooden_skill.h"
#include "wooden_util.h"

// #define debug

namespace test {}

// gen_vector: 生成 vector 形式
/* 本函数形式被删除, 原因是 initializer_list 可以隐式转换为 vector, 以适配
vector 容器类型 template <typename T> inline const std::vector<T>
gen_vector(const int player_num, const std::initializer_list<T> list) {
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
/* 本函数形式被删除, 原因是 initializer_list 可以隐式转换为 vector, 以适配
vector 容器类型 template <typename T1, typename T2> inline const std::map<T1,
T2> gen_map(const int player_num, const std::initializer_list<T1> list1,
std::initializer_list<T2> list2) { assert(list1.size() == player_num);
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

/*
// gen_qi: 生成带 float 的 map 形式
template <typename T1>
inline const std::map<T1, float> gen_qi(const int player_num, const
std::initializer_list<T1> list1, std::initializer_list<float> list2) {
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

namespace tutil {
// TESTN: 打包测试样例的结构
struct TESTN {
    int player_num;                // 测试中的玩家个数
    std::vector<int> players;      // 测试初始的玩家 id
    std::map<int, int> qi;         // 测试初始的气数列表
    std::map<int, bool> tag_died;  // 测试初始的玩家死亡信息
    std::map<int, std::map<int, int> > skl_count;  // 测试初始值的招术使用情况
    std::map<int, tskl::skill> using_skill;  // 测试小局中玩家的出招
    std::map<int, int> target;         // 测试小局中玩家出招的对手
    std::map<int, bool> res_tag_died;  // 测试期望的玩家死亡信息
    std::map<int, int> res_qi;         // 测试期望的气数列表

    std::string comment;  // 备注

    TESTN();

    // TESTN: 玩家人数, 玩家id, 气数, 死亡标记, 招术计数器, 期望死亡标记,
    // 期望气数, 备注
    TESTN(int _player_num, std::vector<int> _players, std::map<int, int> _qi,
          std::map<int, bool> _tag_died,
          std::map<int, std::map<int, int> > _skl_count,
          std::map<int, tskl::skill> _using_skill, std::map<int, int> _target,
          std::map<int, bool> _res_tag_died, std::map<int, int> _res_qi,
          std::string _comment);

    void info() const;
};
}  // namespace tutil

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

// gdp => gen_default_player
#define gdp gen_default_player

// gq => 生成气形式的 map => gen_map<int, int>
#define gq gen_map<int, int>

// gqx => 生成气形式的 mapx => gen_mapx<int, int>
#define gqx gen_mapx<int, int>

// grv => gen_repeated_vec
#define grv gen_repeated_vec

// gsc => 生成技能计数形式的 map => gen_map<int, std::map<int, int> >
#define gsc gen_map<int, std::map<int, int> >

// gal => gen_all_alive
#define gal gen_all_alive

// gu => 生成使用技能的计数形式的 map => gen_map<int, tutil::skill>
#define gu gen_map<int, tskl::skill>

// gcs => gen_cleared_skl()
#define gcs gen_cleared_skl()

// gmap(x) => gen_map<int, x>
#define gmap(x) gen_map<int, x>

extern const tutil::TESTN test13;

void passon(const tutil::TESTN &, bool);

#endif  // WOODEN_TEST_H
