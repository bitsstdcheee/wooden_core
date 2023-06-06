#ifndef WOODEN_GAME_WOODEN_JUDGE_H
#define WOODEN_GAME_WOODEN_JUDGE_H
#include "wooden_skill.h"
#include "wooden_status.h"

#include <array>
#include <cassert>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iomanip>
#include <iostream>
#include <map>
#include <new>
#include <sstream>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

using namespace tskl;

// NUM_SKL 的宏定义版本, 应该和 NUM_SKL 的值相等
// 用于模板定义, 因为在定义和实现的分离的情况下的常量无法用作模板常量
// (要求编译器时就应解析为常数, 而不是链接)
#define NUM_SKL_M 29

extern int player_num;
extern const int MAX_PLAYER_NUM;

// players: 记录每位玩家的 id, 无序
// 指向 vector 的指针, 用于明确 player_num 后分配空间大小
extern std::vector<int> *players;

// std::vector<int> *players = new std::vector<int>(4);

// qi: 记录每位玩家 (id) 对应当前的气数
extern std::map<int, int> qi;

// tag_died: 记录每位玩家 (id) 对应的死亡状态
// false: 当前未死亡
// true: 当前已死亡 / 出局 / 隐退
extern std::map<int, bool> tag_died;

// skl_count: 记录每位玩家 (id) 对应技能 (skl) 使用次数
extern std::map<int, std::map<int, int> > skl_count;

// init: 玩家信息的初始化
void init();

float formatx(int);

string formatxstr(int);

// NUM_SKL: 当前招式个数 (id 最大值)
extern const int NUM_SKL;

// Skill: 带有对象的招术封装
struct Skill {
    tskl::skill skl;

    // 招数实施对象
    int target;

    // 显式转换 Skill -> skill
    operator tskl::skill();

    Skill();

    Skill(tskl::skill, int);

    /*
    Skill(tskl::skill _skl, int _target) {
        skl = skill(_skl);
        target = _target;
    }
    */
};

struct SkillPack {
    std::vector<Skill> skills;
    explicit operator std::vector<tskl::skill>();
    SkillPack();
    explicit SkillPack(std::vector<Skill> _skills);

    // 强制返回第一个 Skill 来缩减类型, 不推荐使用
    Skill narrow_skill();
};

// have_att: 检测玩家是否发出了攻击性招术
// true: 有
// false: 无
bool have_att(const std::pair<int, Skill> &);

// have_axe: 检测玩家是否有镐子招术
bool have_axe(const std::pair<int, Skill> &);

// have_clap_axe: 检测玩家是否有拍气 / 镐子招术
// true: 有
// false: 无
bool have_clap_axe(const std::pair<int, Skill> &);

// clean_choices: 清洗玩家选择: 对于已死去的玩家的技能清除
std::vector<std::pair<int, Skill> > clean_choices(
    const std::vector<std::pair<int, Skill> > &);

// skl_max_defense: 记录 skill 对应防御的最大值 (x100)
// 此处不算攻击带来的防御
extern const std::array<int, NUM_SKL_M> skl_max_defense;

// skl_min_defense: 记录 skill 对应防御的最小值 (x100)
extern const std::array<int, NUM_SKL_M> skl_min_defense;

// skl_attack: 记录 skill 对应攻击 (x100)
extern const std::array<int, NUM_SKL_M> skl_attack;

// skl_qi: 记录 skill 对应使用的气数 (x100)
extern const std::array<int, NUM_SKL_M> skl_qi;

// skl_qi_add: 记录换气后应加的气 (x100)
extern const std::array<int, NUM_SKL_M> skl_qi_add;

// get_skl_defense: 获取并返回 skl 对应拥有的防御值
std::pair<int, int> get_skl_defense(const skill &);

// get_skl_attack: 获取并返回 skl 对应拥有的攻击值
int get_skl_attack(const skill &skl);

// check_available: 检查当前玩家的选择是否合法 (爆气, 超出次数限制)
bool check_available(const std::pair<int, Skill> &choice);

#ifdef using_new_judger

// 记录每个技能在大局中的最高可用次数 (-1 为无限,)
extern const int max_skl_count[NUM_SKL_M];

// 完成 Skill -> SkillPack 的显式转换
std::vector<std::pair<int, SkillPack> > skillPack(
    const std::vector<std::pair<int, Skill> > &);

// 清洗数据 (已死亡的玩家)
// choices: player_id -> SkillPack
std::vector<std::pair<int, SkillPack> > clean_choices(
    const std::vector<std::pair<int, SkillPack> > &);

// 记录当前小局中玩家上一次出招
extern std::map<int, skill> player_last_skill;

// do_main: 主小局判定程序 (新方法)
// dirty_choices: 玩家的招式选择
void do_main(const std::vector<std::pair<int, SkillPack> > &);

#else  // using_new_judger
// do_main：主小局判定程序
// choices: player_id, skill
void do_main(const std::vector<std::pair<int, Skill> > &);

#endif  // using_new_judger

// pretty_print_result_died: 格式化打印玩家死亡信息
// _id: 玩家 id 列表
// _tag_died: 玩家死亡信息, 格式应与 tag_died 相同
// comment: 可选, 作为输出辅助信息
void pretty_print_result_died(const std::vector<int> &,
                              const std::map<int, bool> &,
                              const std::string & = "");

// pretty_print_result_qi: 格式化打印玩家气数信息
// _id: 玩家 id 列表
// _qi: 玩家气数信息, 格式应与 qi 相同
// comment: 可选, 作为输出辅助信息
void pretty_print_result_qi(const std::vector<int> &,
                            const std::map<int, int> &,
                            const std::string & = "");

// continue_game: 大局中两个小局间的衔接
// now: 当前每个玩家的状况
// n: 当前即将进行的局数
game_status continue_game(int, game_status,
                          const std::vector<std::pair<int, Skill> > &);

#endif  // WOODEN_GAME_WOODEN_JUDGE_H