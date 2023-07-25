#ifndef WOODEN_UTIL_H
#define WOODEN_UTIL_H

#include <array>
#include <cassert>
#include <initializer_list>
#include <iostream>
#include <map>
#include <new>
#include <string>
#include <utility>
#include <vector>

#include "wooden_skill.h"

// gen_map: 生成 map 形式
template <typename T1, typename T2>
const std::map<T1, T2> gen_map(const int player_num, const std::vector<T1> vec1,
                               const std::vector<T2> vec2);

// gen_mapx: 生成 map 形式 (x100)
template <typename T1, typename T2>
const std::map<T1, T2> gen_mapx(const int player_num,
                                const std::vector<T1> vec1,
                                const std::vector<T2> vec2);

// gen_repeated_vec: 生成重复一个对象的 vec
template <typename T>
const std::vector<T> gen_repeated_vec(const T obj, const int times);

const std::vector<int> gen_default_player(const int);

const std::map<int, int> gen_cleared_skl();

const std::map<int, bool> gen_all_alive(const std::vector<int> &);

// equal_map: 用于测试用例和实际结果的 map 容器比较
// _id: 玩家 id 列表
// _mp1: 待比较的 _mp1
// _mp2: 待比较的 _mp2
template <typename T>  // 调用模板函数不一定需要写出此处模板函数定义的 T
bool equal_map(const std::vector<int> &, const std::map<int, T> &,
               const std::map<int, T> &);

// 生成默认的玩家列表
// player_num: 玩家数量
const std::vector<int> gen_players(const int);

const std::map<int, int> gen_qi(std::initializer_list<int>, bool = true);

const std::map<int, int> gen_qi(std::initializer_list<int>,
                                std::initializer_list<int>, bool = true);

const std::map<int, bool> gen_tag_died(std::initializer_list<bool>);

const std::map<int, bool> gen_tag_died(const int);

const std::map<int, std::map<int, int> > gen_skl_count(
    std::initializer_list<std::map<int, int> >);

const std::map<int, tskl::skill> using_skill(
    std::initializer_list<tskl::skill>);

const std::map<int, int> gen_target(std::initializer_list<int>);

const std::map<int, bool> gen_res_tag_died(std::initializer_list<bool>);

const std::map<int, int> gen_res_qi(std::initializer_list<int>);

#include "wooden_util.inl"

#endif  // WOODEN_UTIL_H