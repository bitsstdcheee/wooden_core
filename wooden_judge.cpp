#include <array>
#include <cstdio>
#include <exception>
#include <iostream>
#include <new>
#include <ostream>
#include <cstdlib>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
#include <map>
#include <cassert>

#include "wooden_test.h"
#include "wooden_status.h"
#include "wooden_skill.h"
#include "wooden_judge.h"
#include "wooden_debug.h"

using namespace tutil; // 直接 using namespace 省去前缀
using namespace tskl;
// using namespace std;

#define using_new_judger

/*
#ifndef debug

// CMT_HOLD: 宏函数更换为注释, 用于占位避免注释符号比宏更先处理
#define CMT_HOLD 
#define dprint(x,...) /CMT_HOLD*dprint(x)*CMT_HOLD/
#undef CMT_HOLD
#endif
*/

int player_num;
// players: 记录每位玩家的 id, 无序
// 指向 vector 的指针, 用于明确 player_num 后分配空间大小
std::vector<int>* players;
// std::vector<int> *players = new std::vector<int>(4);
// qi: 记录每位玩家 (id) 对应当前的气数
std::map<int, float> qi;  
// tag_died: 记录每位玩家 (id) 对应的死亡状态
// false: 当前未死亡
// true: 当前已死亡 / 出局 / 隐退
std::map<int, bool> tag_died;
// skl_count: 记录每位玩家 (id) 对应技能 (skl) 使用次数
std::map<int, std::map<int, int> > skl_count;

// init: 玩家信息的初始化
void init() {
    dprint("[Init] player_num = " + std::to_string(player_num));
    /* try {
        std::cout << "Address: " << new std::vector<int>(player_num) << std::endl;
        // players = new std::vector<int>(player_num); // 修复后续 for 循环中出现 vector 段错误的 bug
        // players = new std::vector<int>(4);
    }
    // catch (std::bad_alloc &memExp) {
    //     dprint("Exp!: ", false);
    //     dprint(memExp.what());
    //     abort();
    // }
    catch (std::exception &e) {
        dprint("Exp!: ", false);
        dprint(e.what());
    } */
    
    // if (players == 0) {
    //     dprint("players is 0!");
    //     assert(players != 0);
    // }

    players = new std::vector<int>(player_num);
    // dprint("After new vector players");

    for (int i = 0; i < player_num; i++) {
        // dprint("i = " + std::to_string(i));
        (*players)[i] = 0;   // 此处默认改成 0
        // dprint("After 1");
        qi[(*players)[i]] = 0;
        // dprint("After 2");
        tag_died[(*players)[i]] = false;
        // dprint("After 3");
        // (抛弃) 此处的 tag_died 应先预设为 true, 当玩家确认开始游戏时更改为 false
        skl_count[(*players)[i]].clear();
        // dprint("After 4");
    }
}


// TODO: 添加全局伤害招术 Hither, 羊驼
// TODO: 添加多镐子 / 多把剑 以及多目标的功能
// TODO: 添加特殊招术: 拳, Pia, 空手, YG, 拆, 管, Gulu~Gulu~, 评测, 金身
// TODO: 添加更改判定死亡顺序: 爆气, 评测, 管, Gulu~Gulu~, 伤害结算, 镐子结算
// TODO: [MOD] 续气
// TODO: [MOD] Fire
// TODO: [Future] 代码生成混淆

const int NUM_SKL = 19;

// Skill: 带有对象的招术封装
struct Skill {
    tskl::skill skl;
    int target;  // 招数实施对象
    // 显式转换 Skill -> skill
    operator tskl::skill() {
        // 无招术, 自动转换
        return skl;
    }
    Skill() {
        skl = tskl::none;
        target = 0;
    }
    Skill(tskl::skill _skl, int _target) {
        skl = _skl;
        target = _target;
    }
    /*
    Skill(tskl::skill _skl, int _target) {
        skl = skill(_skl);
        target = _target;
    }
    */
};

struct SkillPack {
    std::vector<Skill> skills;
    explicit operator std::vector<tskl::skill>() {
        if (skills.empty()) {
            std::vector<tskl::skill> res;
            res.clear();
            return res;
        }
        std::vector<tskl::skill> res(skills.size());
        int idx = 0;
        for (auto i = skills.begin(); i != skills.end(); i++, idx++) {
            res[idx] = (tskl::skill)(skills[idx]);
        }
        return res;
    }

    SkillPack() {
        skills.clear();
    }

    explicit SkillPack(std::vector<Skill> _skills) {
        skills = std::move(_skills);
    }

    // 强制返回第一个 Skill 来缩减类型, 不推荐使用
    Skill narrow_skill() {
        if (skills.empty()) return Skill();
        return skills[0];
    }
};

// have_att: 检测玩家是否发出了攻击性招术
// true: 有
// false: 无
bool have_att(const std::pair<int, Skill> &choice) {
    switch (choice.second.skl) {
        case wooden_sword: case yellow_sword:
        case stone_sword: case iron_sword:
        case gold_sword: case diamond_sword:
        case enchanted_sword:
        case hither:
            return true;

        default:
            break;
    }
    return false;
}

// have_axe: 检测玩家是否有镐子招术
bool have_axe(const std::pair<int, Skill> &choice) {
    switch (choice.second.skl) {
        case clap: case wooden_axe:
        case normal_axe: case diamond_axe:
        case enchanted_axe:
            return true;
        default:
            break;
    }
    return false;
}

// have_clap_axe: 检测玩家是否有拍气 / 镐子招术
// true: 有
// false: 无
bool have_clap_axe(const std::pair<int, Skill> &choice) {
    if (have_axe(choice)) return true;
    switch (choice.second.skl) {
        case clap:
            return true;
        default:
            break;
    }
    return false;
}

// clean_choices: 清洗玩家选择: 对于已死去的玩家的技能清除
std::vector<std::pair<int, Skill> > clean_choices(const std::vector<std::pair<int, Skill> > &choices) {
    std::vector<std::pair<int, Skill> > res;
    res.clear();
    for (const auto & player: choices) {
        if (tag_died[player.first] == true) {
            continue;
        }
        res.push_back(player);
    }
    return res;
}

// maxd: 记录 skill 对应防御的最大值
const std::array<float, NUM_SKL> maxd = {0, 
    0, 0, 0.5, 1, 2.5, 
    1, 2.5, 2, 3, 4, 
    5, 6, 3, 5, 6, 
    5, -1, 0  // -1 为无限
};

// mind: 记录 skill 对应防御的最小值
const std::array<float, NUM_SKL> mind = {0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 1, 1,
    0, 0, 0
};

// attk: 记录 skill 对应攻击
const std::array<float, NUM_SKL> attk = {0,
    0, 0, 0, 0, 0,
    1, 2.5, 2, 3, 4,
    5, 6, 0, 0, 0,
    0, 0, 1
};

// sklqi: 记录 skill 对应使用的气数
const std::array<float, NUM_SKL> sklqi = {0,
    0, 1, 2, 3, 6,
    1, 1, 2, 3, 4,
    5, 6, 0, 0, 0,
    0, 0, 0
};

std::pair<float, float> get_skl_defense(const skill &skl) {
    // get_skl_defense: 获取并返回 skl 对应拥有的防御值
    return std::make_pair(mind[skl], maxd[skl]);
}

float get_skl_attack(const skill &skl) {
    // get_skl_attack: 获取并返回 skl 对应拥有的攻击值
    return attk[skl];
}

bool check_available(const std::pair<int, Skill> &choice) {
    // check_available: 检查当前玩家的选择是否合法 (爆气, 超出次数限制)
    if (qi[choice.first] < sklqi[choice.second.skl]) return false;  // 气不够
    Skill cskl = choice.second;
    int id = choice.first;
    if (cskl == ashiba && skl_count[id][cskl.skl] >= 2) {
        // ashiba 阿西巴 每小局限制 2 次
        return false;
    } 
    if (cskl == zd && skl_count[id][cskl.skl] >= 1) {
        // zd 每小局限制 1 次
        return false;
    }
    if (cskl == hither && skl_count[id][cskl.skl] >= 1) {
        return false;
    }
    return true;
}

#ifdef using_new_judger

/* 在新的 Judger using_new_judger 中, 使用新的数据输入方式和处理方式
 * 
 * 在每次小局开始时, 需要调用 init_judge() 来初始化
 * 
 * 在一个小局中, 考虑到延迟招式的存在, 调用者需要不断通过获取 check_need_more() 函数
 * 来判断是否需要继续向玩家询问延迟招式, 并获取当前需要询问出招的玩家 (若还有相较更晚决定
 * 招式的玩家则需要在下一次调用相同函数时处理, 而本次不会返回这些玩家)
 * 
 * do_main() 是游戏主逻辑函数, 无论是小局开始的第一次还是延迟出招, 都要交给这个函数处理,
 * 这意味着 do_main() 在新的判定方式中带有状态性 (原来的判定方式并不支持延迟出招, 因此
 * 以无状态的方式实现, 也便于调用), 但是调用者并不需要特意处理状态性带来的问题, 但调用着
 * 应遵守一个原则: 只往参数中传递新的招式. "以不变应万变", do_main() 不需要额外的提示
 * 即可自动处理小局起始出招或者接续出招.
 * 
 * do_main() 只是一个处理函数, 不返回任何值, 调用者需通过 query_player_status() 
 * 来获取当前每个玩家的状态 (存活/死亡) 、气数和死亡原因
 *
 */

// 完成 Skill -> SkillPack 的显式转换
std::vector<std::pair<int, SkillPack> > skillPack(const std::vector<std::pair<int, Skill> > &choices) {
    std::vector<std::pair<int, SkillPack> > res;
    res.clear();
    for (auto i: choices) {
        SkillPack tmp;
        tmp.skills.clear();
        tmp.skills.push_back(i.second);
        res.push_back(std::make_pair(i.first, tmp));
    }
    return res;
}


// 清洗数据 (已死亡的玩家)
// choices: player_id -> SkillPack
std::vector<std::pair<int, SkillPack> > clean_choices(const std::vector<std::pair<int, SkillPack> > &choices) {
    std::vector<std::pair<int, SkillPack> > res;
    res.clear();
    for (auto & player : choices) {
        if (tag_died[player.first] == true) {
            continue;
        }
        res.push_back(player);
    }
    return res;
}

// 记录当前小局中玩家上一次出招
std::map<int, skill> player_last_skill;

// do_main: 主小局判定程序 (新方法)
// dirty_choices: 玩家的招式选择
void do_main(const std::vector<std::pair<int, SkillPack> > &dirty_choices) {
    // Step 1: 清洗数据
    std::vector<std::pair<int, SkillPack> > choices = clean_choices(dirty_choices);

    // Step 2: 检查是否有空出招
    for (auto player: choices) {
        if (player.second.skills.size() < 1) {
            dprint("[Step 2] 玩家 " + std::to_string(player.first) + " 没有任何出招但出现在参数中");
        }
    }

    // Step 2: 处理招式叠加是否允许
    for (auto player: choices) {
        auto& pid = player.first;
        auto& psp = player.second;
        auto& pls = player_last_skill[pid];

        // 扫描一遍招式叠加情况

        // 是否含有不可叠加的招式
        bool have_unoverlay = false;
        bool have_failed = false;
        bool have_overlay_group = false;
        std::string overlay_group_id = "";
        for (auto skl: psp.skills) {
            if (query_skill_can_overlay(skl) == false) {
                // 当前招式不允许叠加
                have_unoverlay = true;
                if (psp.skills.size() > 1) {
                    // 同时出的不同种类招式数 > 1 并且有不可叠加的招式时, 必不合法
                    dprint("[Step 2] 检测到不合法输入 (player: " + std::to_string(pid) + "), 不同种类招式数:" + std::to_string(psp.skills.size()) + ", 不可叠加 skill_id:" + std::to_string(skl));
                    have_failed = true;
                    break;
                }
            }
            else {
                // 当前招式允许叠加
                std::string ogid = tskl::query_skill_overlay_name(skl);
                if (!have_overlay_group) {
                    have_overlay_group = true;
                    overlay_group_id = ogid;
                }
                else {
                    if (overlay_group_id != ogid) {
                        // 之前已有允许叠加的招式且叠加组 id 不一致
                        dprint("[Step 2] 检测到不合法输入 (player: " +
                        std::to_string(pid) + "), 多个叠加组 id, 新 id:" + ogid + ", 旧 id:" + overlay_group_id);
                        have_failed = true;
                        break;
                    }
                }
            }
        }
        dprint("[Step 2] 玩家" + std::to_string(pid) + " " + (std::string)(have_unoverlay ? "有" : "没有") + "不可叠加的招式");
        if (have_failed) {
            dprint("[Step 2] 玩家 " + std::to_string(pid) + " " + "不合法出招, 判死");
            tag_died[pid] = true;
        }
    }

    choices = clean_choices(choices);
    
    // Step 2: 处理不合法输出 (多次咕噜咕噜, 管类后出无关招式)
    for (auto player : choices) {
        auto& pid = player.first;
        auto& psp = player.second;
        assert(psp.skills.size() > 0);
        auto& default_skl = psp.skills[0]; // 假设第一个就是玩家选的 (通常招式列表只有一个)
        auto& pls = player_last_skill[pid];
        if (!pls) continue;
        if (pls == tskl::none) continue;
        if (pls == tskl::gulu) {
            // 上一次使用咕噜咕噜, 本次禁用咕噜咕噜
            if (default_skl == tskl::gulu) {
                dprint("[Step 2] 玩家 " + std::to_string(pid) + " 连续使用咕噜咕噜, 判死");
                tag_died[pid] = true;
                continue;
            }
        }
        if (pls == tskl::tube) {
            // 上一次使用管类, 这次只能出管
            // 管类中, 第一次传递的管类不含对象, 代表该玩家使用管类; 第二次传递的管类包含使用对象, 代表玩家延迟决定后的使用对象;
            // 在第一次管类中, last_skill 设为 tube; 在第二次管类决定对象后, last_skill 设为 none
            if (default_skl != tskl::tube) {
                dprint("[Step 2] 玩家 " + std::to_string(pid) + " 在上一次使用了管类延迟, 但在这次中并没有正确向攻击对象发出管, 而是使用招式 id=" + std::to_string(default_skl) + ", 判死");
                tag_died[pid] = true;
                continue;
            }
        }
    }
}
#else

// do_main：主小局判定程序
// choices: player_id, skill
void do_main(const std::vector<std::pair<int, Skill> > &dirty_choices) {

    //// 定义区域 - 开始
    std::map<int, float> qi_add; // id -> qi
    // qi_add: 记录当前小局该玩家应得的气数, 但未加到计数器
    qi_add.clear();

    std::vector<std::pair<int, Skill> > choices = clean_choices(dirty_choices);

    //// 定义区域 - 结束

    // Step 0. 出招合法性
    bool has_died_er = false; //是否已死人
    for (const auto & player_choice: choices) {
        if (check_available(player_choice) == false) {
            // 不合法
            tag_died[player_choice.first] = true;
            has_died_er = true;
            dprint("[Step 0] 玩家 " + std::to_string(player_choice.first) + " 检测出招不合法, tag_died 设为 true");
        } 
    }
    dprint("[Step 0] 完成, has_died = ", false);
    if (has_died_er == true) {
        #ifndef debug
        choices = clean_choices(choices);
        #endif
        dprint("true");
    }
    else {
        dprint("false");
    }

    // Step 0.5. 添加计数器
    // 合法性检查通过, 将玩家选择的招式加入计数器
    for (const auto & player: choices) {
        #ifndef debug
        assert(tag_died[player.first] == false);
        #endif
        skl_count[player.first][player.second.skl] ++;
        dprint("[Step 0.5] 玩家 " + std::to_string(player.first) + " 技能为 " + std::to_string(player.second.skl));
    }

    // Step 1. 处理拍气

    // 当前小局中是否有人拍气, 用于木镐判定
    bool has_clap = false;

    for (const auto & player_choice : choices) {
        assert(tag_died[player_choice.first] != true); // 理论上来说 choice 没有已死亡玩家了
        if (tag_died[player_choice.first] == true) {
            dprint("[Step 1] 玩家 " + std::to_string(player_choice.first) + " 已死亡, 跳过");
        }
        /*
        if (tag_died[player_choice.first] == true) {
            dprint("[Step 1] 玩家 " + std::to_string(player_choice.first) + " 已死亡, 跳过");
            continue;
        }
         */
        if (player_choice.second.skl == clap) {
            dprint("[Step 1] 玩家 " + std::to_string(player_choice.first) + " 出 clap, qi_add++");
            qi_add[player_choice.first] ++;
            has_clap = true;
        }
    }

    // Step 2. 拍气导致木镐触发判定
    bool has_died_wooden_axe = false;
    if (has_clap == true) {
        dprint("[Step 2] 存在 Clap, 进入判定");
        for (const auto & player_choice: choices) {
            dprint("[Step 2] 玩家 " + std::to_string(player_choice.first)+ ": ", false);
            if (player_choice.second.skl == wooden_axe) {
                tag_died[player_choice.first] = true;
                has_died_wooden_axe = true;
                dprint("出木镐, 判死");
            }
            else {
                dprint("跳过");
            }
        }
    }
    else {
        dprint("[Step 2] 不存在 Clap, 跳过");
    }
    dprint("[Step 2] 完成, has died = ", false);
    if(has_died_wooden_axe == true) {
#ifndef debug
        choices = clean_choices(choices);
#endif
        dprint("true");
    }
    else {
        dprint("false");
    }

#ifdef STEP_3_USE_OLD
    // Step 3. 对于每两个不同的玩家之间进行对决判定
    bool has_died_in_att = false;
    // axe_lose: 标记玩家是否有镐类等值爆现象
    std::map<int, bool> axe_lose;
    axe_lose.clear();
    // has_died_in_att: 是否有人在对决阶段死去, 用于剪枝
    for (const auto & player1 : choices) {
        if (tag_died[player1.first] == true) {
            dprint("[Step 3] P1 = " + std::to_string(player1.first) + ", 已死亡, 跳过");
            // player1 已经死了
            continue;
        }
        for (const auto & player2 : choices) {
            dprint("[Step 3] P1 = " + std::to_string(player1.first) + ", P2 = " + std::to_string(player2.first) + ": ", false);
            //// 初始剪枝 - 开始
            if (player1.first == player2.first) {
                // 相同的两个玩家, 跳过
                dprint("相同玩家, 跳过");
                continue;
            }
            if (player1.first > player2.first) {
                dprint("重复枚举, 跳过");
                continue;
            }
            if (tag_died[player2.first == true]) {
                // player2 已经死了
                dprint("P2(" + std::to_string(player2.first) +") 已经死亡, 跳过");
                continue;
            }
            if (have_att(player1) == 0 && have_att(player2) == 0) {
                // 两人同时没有攻击类
                dprint("P1 与 P2 均没有出攻击类, 跳过");
                continue;
            }
            dprint("");
            //// 初始剪枝 - 结束
            dprint("[Step 3] \t初始剪枝: 结束");

            // TODO: 当前并没有考虑多人围攻一人的情况 (单人可以防御, 但叠加后超过防御最大值)
            //// 伤害判定 - 开始
            // 剩下的是有人拥有攻击类的情况
            std::pair<float, float> def1, def2;
            // def1, def2: 定义为当前 player1 和 player2 所拥有的防御值, 下限与上限
            def1 = def2 = std::make_pair(0, 0);
            def1 = get_defense(player1.second.skl);
            def2 = get_skl_defense(player2.second.skl);
            dprint("[Step 3] \t获取玩家 " + std::to_string(player1.first) + " 的防御值为 [" + std::to_string(def1.first) + ", " + std::to_string(def1.second) + "], 玩家 " + std::to_string(player2.first) + " 的防御值为 [" + std::to_string(def2.first) + ", " + std::to_string(def2.second) + "]");
            float att1, att2;
            // att1, att2: 定义为当前 player1 和 player2 所发出的攻击值
            // 只有当 target 命中时才有攻击
            att1 = get_attack(player1.second.skl) * bool(player1.second.target == player2.first);
            att2 = get_skl_attack(player2.second.skl) * bool(player2.second.target == player1.first);
            dprint("[Step 3] \t获取玩家 " + std::to_string(player1.first) + " 的攻击值为 " + std::to_string(att1) + ", 玩家 " + std::to_string(player2.first) + " 的攻击值为 " + std::to_string(att2));
            if (def1.second == -1) {
                dprint("[Step 3] \t玩家 " + std::to_string(player1.first) + " 具有无限防御, 跳过");
                // 玩家1 拥有无限防御, 双方无实际伤害, 伤害判定跳过
            }
            else if (def2.second == -1) {
                dprint("[Step 3] \t玩家 " + std::to_string(player2.first) + " 具有无限防御, 跳过");
                // 玩家2 拥有无限防御, 双方无实际伤害, 伤害判定跳过
            }
            else {
                dprint("[Step 3] \t进入对战状态: ", false);
                if (att1 > att2) {
                    float dd = att1 - att2;
                    dprint("P1 攻击值大于 P2, 差值为 " + std::to_string(dd) + ", ", false);
                    if (!((dd >= def2.first) && (dd <= def2.second))) {    
                        tag_died[player2.first] = true;
                        has_died_in_att = true;
                        dprint("P2 被攻击致死", false);
                        // player2 被攻击致死
                    }
                    else if (have_axe(player2)) {
                        dprint("检测到 P2 有镐类, ", false);
                        if (def2.second == dd) {
                            axe_lose[player2.first] = true;
                            dprint("P2 等值爆", false);
                        }
                        else {
                            dprint("P2 镐类未爆", false);
                        }
                    }
                }
                else if (att1 < att2) {
                    float dd = att2 - att1;
                    dprint("P1 攻击值小于 P2, 差值为 " + std::to_string(dd) + ", ", false);
                    if (!((dd >= def1.first) && (dd <= def1.second))) {    
                        tag_died[player1.first] = true;
                        has_died_in_att = true;
                        dprint("P1 被攻击致死", false);
                        // player1 被攻击致死
                    }
                    else if (have_axe(player1)) {
                        dprint("检测到 P1 有镐类, ", false);
                        if (def1.second == dd) {
                            axe_lose[player1.first] = true;
                            dprint("P1 等值爆", false);
                        }
                        else {
                            dprint("P1 镐类未爆", false);
                        }
                    }
                }
                else {
                    dprint("[Step 3] \t双方抵消, 继续", false);
                    // 双方抵消, 游戏继续进行
                }
            }
            //// 伤害判定 - 结束
            
            dprint("");

            //// 黄剑判定部分 - 开始
            dprint("[Step 3] \t黄剑判定部分: 开始");
            bool tmp_make_1_died, tmp_make_2_died;
            // tmp_make_X_died: 标记因黄剑而死亡的玩家, 而双方同时出黄剑时同时死,
            // 因此死亡标记修改应在判定完成之后
            tmp_make_1_died = tmp_make_2_died = false; 
            if (player1.second.skl == yellow_sword && tag_died[player2.first] == false) {
                // player1 未能使用黄剑杀死 player2
                tmp_make_1_died = true;
                has_died_in_att = true;
                dprint("[Step 3] \tP1 出黄剑, P2 上阶段未死, P1 置死");
            }
            if (player2.second.skl == yellow_sword && tag_died[player1.first] == false) {
                // player2 未能使用黄剑杀死 player1
                tmp_make_2_died = true;
                has_died_in_att = true;
                dprint("[Step 3] \tP2 出黄剑, P1 上阶段未死, P2 置死");
            }
            tag_died[player1.first] |= tmp_make_1_died;
            tag_died[player2.first] |= tmp_make_2_died;
            dprint("[Step 3] \t更新死亡状态, P1(" + std::to_string(player1.first) + ") = " + (tag_died[player1.first] == true ? "true": "false") + ", P2(" + std::to_string(player2.first) + ") = " + (tag_died[player2.first] == true ? "true": "false"));
            dprint("[Step 3] \t黄剑判定部分: 结束");
            //// 黄剑判定部分 - 结束

            //// 剪枝优化部分 - 开始
            dprint("[Step 3] \t剪枝优化部分: 开始");
            if (tag_died[player1.first] == true) {
                // player1 已经判死, 第二层循环可以剪枝跳过
                dprint("[Step 3] \t此时 P1(" + std::to_string(player1.first) + ") 已经死亡, break");
                break;
            }
            //// 剪枝优化部分 - 结束
        }
    }
    if (has_died_in_att) {
        // 有玩家在这个步骤中死去, 清理
        dprint("[Step 3] has died = true");
        #ifndef debug
        choices = clean_choices(choices);
        #endif
    }
    else {
        dprint("[Step 3] has died = false");
    }
#else
    // Step 3: New, 不同的攻击判断方式
    // has_died_in_att: 是否有人在对决阶段死去, 用于剪枝
    bool has_died_in_att = false;

    // axe_lose: 记录玩家是否有镐类等值爆现象
    std::map<int, bool> axe_lose;

    axe_lose.clear();
    // suffer_att: 记录该玩家总共受到的伤害
    std::map<int, float> suffer_att;

    // has_def: 记录该玩家拥有防御的 max 和 min
    std::map<int, std::pair<float, float> > has_def;

    suffer_att.clear();
    has_def.clear();

    // Step 3.1: 累计玩家受到攻击, 获取玩家防御值
    int overallHither = 0; // 全场累计 Hither 次数
    for (const auto & player: choices) {
        if (tag_died[player.first] == true) {
            // 死去的玩家不被考虑发出的攻击值
            continue;
        }
        has_def[player.first] = get_skl_defense(player.second.skl);
        dprint("[Step 3.1] 玩家 " + std::to_string(player.first) + " 拥有防御值: [" + std::to_string(has_def[player.first].first) + ", " + std::to_string(has_def[player.first].second) + "], ", false);
        if (player.second.skl == hither) {
            // Hither 特判
            overallHither++;
            dprint("发出 Hither");
        }
        else {
            suffer_att[player.second.target] += get_skl_attack(player.second.skl);  // 该玩家的目标s
            dprint("发出攻击: " + std::to_string(get_skl_attack(player.second.skl)) + " -> " + "玩家 " + std::to_string(player.second.target));
        }
    }

    // Step 3.15: 处理 Hither
    dprint("[Step 3.15] 现有 Hither: " + std::to_string(overallHither));
    for (const auto & player: choices) {
        if (player.second.skl == hither) {
            dprint("[Step 3.15] 玩家 " + std::to_string(player.first) + " 有 Hither, 受到攻击: " + std::to_string(float(overallHither - 1) *
                                                                                                                          get_skl_attack(
                                                                                                                                  hither)));
            suffer_att[player.first] += float(overallHither - 1) * get_skl_attack(hither);
        }
        else {
            dprint("[Step 3.15] 玩家 " + std::to_string(player.first) + " 没有 Hither, 受到攻击: " + std::to_string(float(overallHither) *
                                                                                                                            get_skl_attack(
                                                                                                                                    hither)));
            suffer_att[player.first] += (float)overallHither * get_skl_attack(hither);
        }
    }
    for (const auto & player: choices) {
        dprint("[Step 3.1] 玩家 " + std::to_string(player.first) + " 受到攻击: " + std::to_string(suffer_att[player.first]));
    }

    // Step 3.2: 攻击-防御对抗
    for (const auto & player: choices) {
        if (suffer_att[player.first] == 0) {
            dprint("[Step 3.2] 玩家 " + std::to_string(player.first) + " 没有受到攻击");
            continue;
        }
        if ((suffer_att[player.first] >= has_def[player.first].first) &&
            suffer_att[player.first] <= has_def[player.first].second) {
            dprint("[Step 3.2] 玩家 " + std::to_string(player.first) + " 可以防, ", false);
            // 可以防得住
            if (have_axe(player)) {
                dprint("有镐子, ", false);
                if (has_def[player.first].second == suffer_att[player.first]) {
                    // 有镐子且等值爆
                    axe_lose[player.first] = true;
                    dprint("等值爆");
                }
                else {
                    dprint("不爆");
                }
            }
            else {
                dprint("无镐子");
            }
        }
        else {
            // 防不住
            dprint("[Step 3.2] 玩家 " + std::to_string(player.first) + " 不可防, 置死");
            tag_died[player.first] = true;
            has_died_in_att = true;
        }
    }
    // Step 3.3: 黄剑判定
    for (const auto & player: choices) {
        if (player.second.skl == yellow_sword) {
            // 有黄剑
            if (tag_died[player.second.target] == true) {
                // 攻击对象已死
                continue;
            }
            else {
                // 攻击对象未死, 自己死
                dprint("[Step 3.3] 玩家 " + std::to_string(player.first) + " 出黄剑, 对象为 " + std::to_string(player.second.target) + ", 判定失败, 置死");
                tag_died[player.first] = true;
                has_died_in_att = true;
            }
        }
    }
    if (has_died_in_att == true) {
        #ifndef debug
            choices = clean_choices(choices);
        #endif
    }
#endif

    // FINISH: 镐类等值爆
    // Step 4. 拍气, 镐子
    // bool has_died_in_clap = false; // 该变量暂时不需要
    for (const auto & player: choices) {
        dprint("[Step 4] 玩家 " + std::to_string(player.first) + ": ", false);
        if (tag_died[player.first]) {
            // player 已经死去
            dprint("玩家已死去, 跳过");
            continue;
        }
        if (have_clap_axe(player) == false) {
            // 玩家没有加气类招术
            dprint("玩家没有加气类, 跳过");
            continue;
        }
        if (player.second.skl == clap) {
            // qi_add[player.first] ++;
            // 这里在 Step 1 中已经加过气了, 不需要再加了
            dprint("玩家出拍气, 不再加气");
        }
        else {
            dprint("玩家出镐类, ", false);
            // 剩余的为镐类, Step 0 中已经处理了爆气的情况, 所以不需要判断是否会爆气 
            if (axe_lose[player.first]) {
                dprint("在上阶段等值爆, 不加气");
                continue;
            }
            // ps: 对玩家 skl 的临时引用
            const int& ps = player.second.skl;
            // id: 对玩家 first 的临时引用
            const int& id = player.first;
            if (ps == wooden_axe) {
                qi_add[id] += 3;
                dprint("+3");
            }
            else if (ps == normal_axe) {
                qi_add[id] += 4;
                dprint("+4");
            }
            else if (ps == diamond_axe) {
                qi_add[id] += 6;
                dprint("+6");
            }
            else if (ps == enchanted_axe) {
                qi_add[id] += 12;
                dprint("+12s");
            }
            else {
                // 未知错误
                assert(false);
            }
        }
    }

    // Step 5. qi_add -> qi, 处理 skill 扣气
    for (auto & player: choices) {
        if (tag_died[player.first] == true) {
            dprint("[Step 5] 玩家 " + std::to_string(player.first) + " 已死亡, 跳过扣气");
            continue;
        }
        qi_add[player.first] -= sklqi[player.second.skl];
        dprint("[Step 5] 玩家 " + std::to_string(player.first) + " 出招 " + std::to_string(player.second.skl) + ", 扣气 " + std::to_string(sklqi[player.second.skl]) + ", qi_add = " + std::to_string(qi_add[player.first]));
    }
    for (auto player: *players) {
        if (qi_add[player] == 0) {
            dprint("[Step 5] 玩家 " + std::to_string(player) + " 无加气, 现有气数为 " + std::to_string(qi[player]));
            continue;
        }
        qi[player] += qi_add[player];
        dprint("[Step 5] 玩家 " + std::to_string(player) + " 加气结算: delta 为 " + std::to_string(qi_add[player])+ ", 现有气数为 " + std::to_string(qi[player]));
    }

    // Step 6. 死去玩家 qi = 0
    for (auto player: *players) {
        if (tag_died[player] == true) {
            qi[player] = 0;
            dprint("[Step 6] 玩家 " + std::to_string(player) + " 已死去, 气置 0");
        }
    }
}
#endif

// pretty_print_result_died: 格式化打印玩家死亡信息
// _id: 玩家 id 列表
// _tag_died: 玩家死亡信息, 格式应与 tag_died 相同
// comment: 可选, 作为输出辅助信息
void pretty_print_result_died(const std::vector<int> &_id, const std::map<int, bool>& _tag_died, const std::string& comment = "") {
    std::cout << "------- Died Players";
    if (comment != "") {
        std::cout << " - " << comment;
    }
    std::cout << " -------";
    std::cout << std::endl;
    bool flag = false; // 记录是否输出过已经死去的玩家 id
    for (auto player: _id) {
        if (_tag_died.at(player) == false) continue;
        std::cout << player << "\t";
        flag = true;
    }
    if (flag == false) {
        std::cout << "Empty!";
    }
    std::cout << std::endl;
}

// pretty_print_result_qi: 格式化打印玩家气数信息
// _id: 玩家 id 列表
// _qi: 玩家气数信息, 格式应与 qi 相同
// comment: 可选, 作为输出辅助信息
void pretty_print_result_qi(const std::vector<int> &_id, const std::map<int, float>& _qi, const std::string& comment = "") {
    std::cout << "------- Qi of Players";
    if (comment != "") {
        std::cout << " - " << comment;
    }
    std::cout << " -------";
    std::cout << std::endl;
    for (auto player: _id) {
        std::cout << player << "\t";
    }
    std::cout << std::endl;
    for (auto player: _id) {
        std::cout << _qi.at(player) << "\t";
    }
    std::cout << std::endl;
}

// equal_map: 用于测试用例和实际结果的 map 容器比较
// _id: 玩家 id 列表
// _mp1: 待比较的 _mp1
// _mp2: 待比较的 _mp2
template <typename T> // 调用模板函数不一定需要写出此处模板函数定义的 T
bool equal_map(const std::vector<int> &_id, const std::map<int, T> &_mp1, const std::map<int, T> &_mp2) {
    for (auto player: _id) {
        if (_mp1.at(player) != _mp2.at(player)) return false;
    }
    return true;
}

// continue_game: 大局中两个小局间的衔接
// now: 当前每个玩家的状况
// n: 当前即将进行的局数
game_status continue_game(int n, game_status now, const std::vector<std::pair<int, Skill> >& choices) {
    // Step 1. 转移数据
    players = now.players;
    player_num = now.player_num;
    qi = now.qi;
    tag_died = now.tag_died;
    skl_count = now.skl_count;

    // Step 2. 进行小局
    #ifdef using_new_judger
    do_main(skillPack(choices));
    #else
    do_main(choices);
    #endif

    // Step 3. 获取结果
    game_status changed(player_num, players, qi, tag_died, skl_count);

    // Step 4. 对比
    dprint("The " + std::to_string(n) + "th game: ");
    bool has_died = false;
    for (auto player: *players) {
        if (now.tag_died[player] != changed.tag_died[player]) {
            has_died = true;
            dprint(std::to_string(player) + "\t", false);
        }
    }
    if (has_died == false) {
        dprint("No player");
    } else {
        dprint("", true);
    }
    dprint("Qi of players: ");
    for (auto player: *players) {
        dprint(std::to_string(player) + "\t", false);
    }
    dprint("", true);
    for (auto player: *players) {
        dprint(std::to_string(changed.qi[player]) + "\t", false);
    }
    dprint("", true);
    return changed;
}

// passon: 传递测试参数并运行测试的函数
void passon(const TESTN &test, bool check) {
    dprint("[P*] Entering passon()");
    const int &_player_num = test.player_num;
    assert(_player_num >= 2); // 玩家数量需大于或等于 2

    const std::vector<int> &_players = test.players;
    const std::map<int, float> &_qi = test.qi;
    const std::map<int, bool> &_tag_died = test.tag_died;
    const std::map<int, std::map<int, int> > &_skl_count = test.skl_count;
    const std::map<int, bool> &_res_tag_died = test.res_tag_died;
    const std::map<int, float> &_res_qi = test.res_qi;
    const std::map<int, tskl::skill> &_using_skill = test.using_skill;
    const std::map<int, int> &_target = test.target;
    const std::string &_comment = test.comment;

    // Step 0. 传入数据 -- 玩家个数断言
    dprint("[P0] Before importing data");
    assert(_players.size() == (long long unsigned int)_player_num);
    assert(_qi.size() == (long long unsigned int)_player_num);
    assert(_tag_died.size() == (long long unsigned int)_player_num);
    assert(_skl_count.size() == (long long unsigned int)_player_num);
    assert(_res_tag_died.size() == (long long unsigned int)_player_num);
    assert(_res_qi.size() == (long long unsigned int)_player_num);
    assert(_using_skill.size() == (long long unsigned int)_player_num);
    assert(_target.size() == (long long unsigned int)_player_num);

    // 转换 test::skill -> choices
    dprint("[P0] Before test::skill -> choices");
    auto* _dirty_choices = new std::vector<std::pair<int, Skill> >(_player_num);
    int cnt = 0;
    for (auto i: _using_skill) {
        dprint("[P0] In for: i = <" + std::to_string(i.first) + ", " + std::to_string(i.second) + ">, cnt = " + std::to_string(cnt));
        (*_dirty_choices)[cnt++] = std::make_pair(i.first, Skill(i.second, _target.at(i.first)));  // VS 调试中发现该语句的 vector 容器触发 assert 错误 (已修复)
    }
    dprint("[P0] After test::skill -> choices");

    // Step 1. 拷贝数据
    dprint("[P1] Before copying data");
    player_num = _player_num;
    dprint("[P1] Before entering init()");
    init();
    dprint("[P1] After entering init()");
    (*players) = _players;
    qi = _qi;
    tag_died = _tag_died;
    skl_count = _skl_count;
    dprint("[P2] After copying data");

    // Step 2. 运行测试
    dprint("[P2] Before do_main()");
    #ifdef using_new_judger
    do_main(skillPack(*_dirty_choices));
    #else
    do_main(*_dirty_choices);
    #endif
    dprint("[P2] After do_main()");

    // Step 2.5 打印结果
    pretty_print_result_died((*players), tag_died);
    pretty_print_result_qi((*players), qi);

    pretty_print_result_died((*players), _res_tag_died, _comment);
    pretty_print_result_qi((*players), _res_qi, _comment);
    dprint("[P2.5] After pretty printing");

    if (check == true) {
        // Step 3. 判断结果
        // assert(_res_tag_died == tag_died);
        // assert(_res_qi == qi);
        dprint("[P3] Before assert result");
        assert(equal_map(*players, _res_tag_died, tag_died));
        assert(equal_map(*players, _res_qi, qi));
    }
    else {
        dprint("[P3] I will not check");
    }

    std::cout << "Test success: " << test.comment << std::endl;
}

// 编译环境: C++11
