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

#include "wooden_debug.h"
#include "wooden_judge.h"
#include "wooden_skill.h"

using std::string;

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

const std::map<int, int> gen_qi(const int);

const std::map<int, int> gen_qi(std::initializer_list<int>, bool = true);

const std::map<int, int> gen_qi(std::initializer_list<int>,
                                std::initializer_list<int>, bool = true);

const std::map<int, bool> gen_tag_died(std::initializer_list<bool>);

const std::map<int, bool> gen_tag_died(const int);

const std::map<int, std::map<int, int>> gen_skl_count(
    std::initializer_list<std::map<int, int>>);

const std::map<int, std::map<int, int>> gen_skl_count(const int);

const std::map<int, tskl::skill> gen_using_skill(
    std::initializer_list<tskl::skill>);

const std::map<int, std::vector<tskl::skill>> gen_using_skill(
    std::map<int, std::vector<tskl::skill>>);

const std::map<int, int> gen_target(std::initializer_list<int>);

const std::map<int, bool> gen_res_tag_died(std::initializer_list<bool>);

const std::map<int, int> gen_res_qi(std::initializer_list<int>, bool = true);

#include "wooden_util.inl"

void print_single_skill(const Skill &skl, bool need_endl = false);

// 便捷打印输入 do_main 参数.
// name: 名称.
// line_prefix: 在每行开始时输出的内容, 默认值为 "[P] ".
// len_offset: 计算回收 Sharp 井号所需数量时需要加上 (负数为减去) 的长度数量,
// std::string.length() 在计算时会将全角字符处理为 1, 输出时则需要 2 个井号,
// 故需要在此参数加上. len_offset 理论上为输入字符串中全角字符的数量
void print_batch(const std::vector<std::pair<int, SkillPack>> &batch,
                 std::string name = "", std::string line_prefix = "[P] ",
                 int len_offset = 0, bool print_header = true);
void print_batch(const std::map<int, std::vector<Skill>> &batch,
                 std::string name = "", std::string line_prefix = "[P] ",
                 int len_offset = 0, bool print_header = true);

// 小局中的批次
struct RoundPatch {
    // 编号
    string id;

    // 前驱批次 ID
    string prev_patch;

    // 后继批次 ID
    std::vector<string> next_patch;

    // 玩家列表
    std::vector<int> players;

    // 玩家的气数 (结果)
    std::map<int, int> qi;

    // 玩家的出招 (条件)
    std::map<int, std::vector<Skill>> choices;

    // 玩家的出局情况 (结果)
    std::map<int, bool> tag_died;

    // 玩家的出招计数 (结果)
    std::map<int, std::map<int, int>> skl_count;

    // 玩家本批次计算后的技能使用情况 (结果)
    std::map<int, std::map<tskl::skill, bool>> skill_used;

    // 本批次计算后需要延迟出招的玩家 (结果)
    std::map<int, bool> delayed_players;

    // 当前批次是否已经被计算过
    bool judged;

    // 当前批次是否为第一批次, 用于决定如何处理 delayed_players
    // 默认值为 true
    bool head;

    RoundPatch();

    // 初始化未计算过的小局信息
    // 提供参数: ID, 前驱批次 ID, 玩家列表, 出招, 是否为 Head
    RoundPatch(string _id, string _prev_patch, std::vector<int> _players,
               std::map<int, std::vector<Skill>> _choices, bool _head);

    // 初始化未计算过的小局信息
    // 提供参数: ID, 玩家列表, 出招, 是否为 Head
    RoundPatch(string _id, std::vector<int> _players,
               std::map<int, std::vector<Skill>> _choices, bool _head);

    // 初始化完整计算过的小局信息, 不会检查结果的正确性
    // 提供参数: ID, 前驱批次 ID, 玩家列表, 出招, 气数, 出局情况, 出招计数,
    // 最后技能使用情况, 需要延迟出招的玩家, 是否为 Head 可选参数: 后继批次 ID
    RoundPatch(string _id, string _prev_patch, std::vector<int> _players,
               std::map<int, std::vector<Skill>> _choices,
               std::map<int, int> _qi, std::map<int, bool> _tag_died,
               std::map<int, std::map<int, int>> _skl_count,
               std::map<int, std::map<tskl::skill, bool>> _skill_used,
               std::map<int, bool> _delayed_players, bool _head,
               std::vector<string> _next_patch = std::vector<string>());

    bool operator<(const RoundPatch x) const;

    // 计算批次的结果
    // 返回值代表计算是否成功, 若不成功, 则不会修改结果属性
    // false -> 成功, true -> 不成功
    bool judge(std::map<string, RoundPatch> *data);

    // 打印当前批次的信息
    void print();

    // 生成一个干净的布局 (按人数生成默认递增的玩家 ID)
    static RoundPatch generate_empty(string _id, int player_cnt);

    // 生成一个干净的布局
    static RoundPatch generate_empty(string _id, int player_cnt,
                                     std::vector<int> _players);

    // 连接两个 Patch
    static void link(RoundPatch &father, RoundPatch &son);

    // 连接两个 Patch (给定数据源)
    static void link(std::map<string, RoundPatch> &data, const string father,
                     const string son);
};

#endif  // WOODEN_UTIL_H