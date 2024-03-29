#ifndef WOODEN_JUDGE_CPP
#define WOODEN_JUDGE_CPP
#include "wooden_judge.h"

#include "wooden_debug.h"
#include "wooden_skill.h"
#include "wooden_status.h"
#include "wooden_test.h"

using namespace tutil;  // 直接 using namespace 省去前缀
using namespace tskl;
// using namespace std;

/*
#ifndef debug

// CMT_HOLD: 宏函数更换为注释, 用于占位避免注释符号比宏更先处理
#define CMT_HOLD
#define dprint(x,...) /CMT_HOLD*dprint(x)*CMT_HOLD/
#undef CMT_HOLD
#endif
*/

int player_num;

const int MAX_PLAYER_NUM = 2048;

std::vector<int> *players;

std::map<int, int> qi;

std::map<int, bool> tag_died;

std::map<int, std::map<int, int>> skl_count;

void init() {
    dprint("[Init] player_num = " + std::to_string(player_num));
    /* try {
        std::cout << "Address: " << new std::vector<int>(player_num) <<
    std::endl;
        // players = new std::vector<int>(player_num); // 修复后续 for
    循环中出现 vector 段错误的 bug
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
        (*players)[i] = 0;  // 此处默认改成 0
        // dprint("After 1");
        qi[(*players)[i]] = 0;
        // dprint("After 2");
        tag_died[(*players)[i]] = false;
        // dprint("After 3");
        // (抛弃) 此处的 tag_died 应先预设为 true, 当玩家确认开始游戏时更改为
        // false
        skl_count[(*players)[i]].clear();
        // dprint("After 4");
    }
}

float formatx(int x) { return (float)x / 100; }

string formatxstr(int x) {
    std::stringstream ss;
    ss << std::setiosflags(std::ios::fixed);
    ss << std::setprecision(2) << formatx(x) << std::endl;
    string str;
    ss >> str;
    return str;
}

// TODO: 添加全局伤害招术 Hither, 羊驼
// TODO: 添加多镐子 / 多把剑 以及多目标的功能
// TODO: 添加特殊招术: 拳, Pia, 空手, YG, 拆, 管, Gulu~Gulu~, 评测, 金身
// TODO: 添加更改判定死亡顺序: 爆气, 评测, 管, Gulu~Gulu~, 伤害结算, 镐子结算
// TODO: [MOD] 续气
// TODO: [MOD] Fire
// TODO: [Future] 代码生成混淆

const int NUM_SKL = tskl::MAX_SKILL_NUM;

Skill::operator tskl::skill() {
    // 无招术, 自动转换
    return skl;
}

Skill::Skill() {
    skl = tskl::none;
    target = 0;
}

Skill::Skill(tskl::skill _skl, int _target) {
    skl = _skl;
    target = _target;
}

SkillPack::operator std::vector<tskl::skill>() {
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

SkillPack::SkillPack() { skills.clear(); }

SkillPack::SkillPack(std::vector<Skill> _skills) {
    skills = std::move(_skills);
}

Skill SkillPack::narrow_skill() {
    if (skills.empty()) return Skill();
    return skills[0];
}

bool have_att(const std::pair<int, Skill> &choice) {
    switch (choice.second.skl) {
        case wooden_sword:
        case yellow_sword:
        case stone_sword:
        case iron_sword:
        case gold_sword:
        case diamond_sword:
        case enchanted_sword:
        case hither:
        case bo_sword:
        case fist:
        case palm:
        case tube:
        case alpaca:
        case tube_selected:
            return true;

        default:
            break;
    }
    return false;
}

bool have_axe(const std::pair<int, Skill> &choice) {
    switch (choice.second.skl) {
        case wooden_axe:
        case normal_axe:
        case diamond_axe:
        case enchanted_axe:
            return true;
        default:
            break;
    }
    return false;
}

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

std::vector<std::pair<int, Skill>> clean_choices(
    const std::vector<std::pair<int, Skill>> &choices) {
    std::vector<std::pair<int, Skill>> res;
    res.clear();
    for (const auto &player : choices) {
        if (tag_died[player.first] == true) {
            continue;
        }
        res.push_back(player);
    }
    return res;
}

// clang-format off

const std::array<int, NUM_SKL_M + 1> skl_max_defense = {0, 
    0, 0, int(0.5 * 100), 1 * 100, int(2.5 * 100), 
    0, 0, 0, 0, 0, 
    0, 0, 3 * 100, 5 * 100, 6 * 100, 
    5 * 100, -1, 0, 0, 0,  // -1 为无限
    0, 0, 0, 0, 0, 
    0, 0, 0, 1 * 100, 0,
    0
};

const std::array<int, NUM_SKL_M + 1> skl_min_defense = {0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 1 * 100, 1 * 100,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0
};

const std::array<int, NUM_SKL_M + 1> skl_attack = {0,
    0, 0, 0, 0, 0,
    1 * 100, int(2.5 * 100), 2 * 100, 3 * 100, 4 * 100,
    5 * 100, 6 * 100, 0, 0, 0,
    0, 0, 1 * 100, int(0.5 * 100), int(1.5 * 100),
    int(2.5 * 100), int(0.5 * 100), 0, 0, 0,
    0, 0, 0, 0, 0,
    1 * 100
};

const std::array<int, NUM_SKL_M + 1> skl_qi = {0,
    0, 1 * 100, 2 * 100, 3 * 100, 6 * 100,
    1 * 100, 1 * 100, 2 * 100, 3 * 100, 4 * 100,
    5 * 100, 6 * 100, 0, 0, 0,
    0, 0, 1 * 100, int(0.5 * 100), int(1.5 * 100), 
    1 * 100, int(2 * 100), 1 * 100, 2 * 100, 0,
    0, 0, 0, 1 * 100, 0,
    0
}; 

const std::array<int, NUM_SKL_M + 1> skl_qi_base = {0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 1 * 100, 0, 0,
    0, 0, 0, 0, 0,
    0
};

const std::array<int, NUM_SKL_M + 1> skl_qi_add = {0,
    1 * 100, 3 * 100, 4 * 100, 6 * 100, 12 * 100};

// clang-format on

std::pair<int, int> get_skl_defense(const skill &skl) {
    return std::make_pair(skl_min_defense[skl], skl_max_defense[skl]);
}

int get_skl_attack(const skill &skl) { return skl_attack[skl]; }

bool check_available(const std::pair<int, Skill> &choice) {
    if (qi[choice.first] < skl_qi[choice.second.skl]) return false;  // 气不够
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

int get_player_skill_num(const std::vector<std::pair<int, SkillPack>> &choices,
                         const int &pid, const tskl::skill skl) {
    int res = 0;
    for (auto i : choices) {
        if (i.first != pid) continue;
        for (auto skill : i.second.skills) {
            if (skill == skl) res++;
        }
    }
    return res;
}

std::vector<std::pair<int, SkillPack>> strip_player_skill(
    const std::vector<std::pair<int, SkillPack>> &choices, const int &pid,
    const tskl::skill skl) {
    auto res = std::vector<std::pair<int, SkillPack>>();
    res.clear();
    for (auto i : choices) {
        if (i.first != pid) {
            res.push_back(i);
            continue;
        }
        auto skp = SkillPack();
        for (auto skill : i.second.skills) {
            if (skill == skl) {
                if (skl == tskl::yellow_sword) {
                    skp.skills.push_back(
                        Skill(tskl::yellow_sword_destoryed, skill.target));
                }
                continue;
            }
            skp.skills.push_back(skill);
        }
        res.push_back(std::make_pair(i.first, skp));
    }
    return res;
}

#ifdef using_new_judger

// clang-format off
/* 在新的 Judger using_new_judger 中, 使用新的数据输入方式和处理方式
 *
 * 在每次小局开始时, 需要调用 init_judge() 来初始化
 *
 * 在一个小局中, 考虑到延迟招式的存在, 调用者需要不断通过获取 check_need_more()
 * 函数 来判断是否需要继续向玩家询问延迟招式, 并获取当前需要询问出招的玩家
 * (若还有相较更晚决定 招式的玩家则需要在下一次调用相同函数时处理,
 * 而本次不会返回这些玩家)
 *
 * do_main() 是游戏主逻辑函数, 无论是小局开始的第一次还是延迟出招,
 * 都要交给这个函数处理, 这意味着 do_main() 在新的判定方式中带有状态性
 * (原来的判定方式并不支持延迟出招, 因此 以无状态的方式实现, 也便于调用),
 * 但是调用者并不需要特意处理状态性带来的问题, 但调用着 应遵守一个原则:
 * 只往参数中传递新的招式. "以不变应万变", do_main() 不需要额外的提示
 * 即可自动处理小局起始出招或者接续出招.
 *
 * do_main() 只是一个处理函数, 不返回任何值, 调用者需通过 query_player_status()
 * 来获取当前每个玩家的状态 (存活/死亡) 、气数和死亡原因
 *
 * 原则: 出招并不会因为玩家在本回合中的死亡而消失效果
 * Step 1: 清洗数据
 * Step 2: 检查是否爆气, 验证出招合法性
 * Step 3: 若存在管类, 咕噜咕噜 -> 函数结束, 并等待下一次调用
 * (Step 3 后已经没有还未出招的延迟类技能)
 * Step 4: 计算直接出局类: 若场上有人出拍气或者夹剑, 则出木稿的玩家出局
 * Step 4.5: 展开对群类招式, 由先前简单的单个发起技能, 没有攻击对象转换为 n - 1 个对其余玩家的对单攻击 (招式名称不变)
 * Step 5: 计算每名玩家的防御上下限 (注意攻击招数所带来的防御不算在内)
 * Step 6: 夹剑、夹拳、夹波波剑, 若夹成功, 因去除被夹的武器(或记为报废), 并加气
 * Step 7: 计算每位玩家收到的伤害 (估计时间复杂度 O(n^2)), 对于每个点对点的玩家判定伤害的过程, 对于出招为攻击类的玩家, 为该玩家添加一个盾, 其盾量等于这位玩家对于对手的攻击量, 之后计算并出局不能承受伤害的玩家
 * Step 8: 计算反弹: 对于每个带有反弹招式的玩家, 减免受伤害玩家的伤害, 并转换为对发起方的伤害
 * Step 9: 对于一个玩家, 除了可能受到反弹回来的伤害, 还会受到其他玩家的普通形式的攻击伤害, 将这些伤害叠加, 出局不能承受伤害的玩家
 * Step 10: 破镐: 对于钻镐, 附魔钻镐的出招者: 受伤害数=最大防御数时, 镐子报废, 失去加气的功能
 * Step 11: 黄剑判定, 受黄剑攻击者未出局, 则出黄剑者出局, 注意黄剑的连锁判定情况
 * Step 12: 镐子加气, 拍手加气
 * Step 13: 为所有已出局玩家的气数清零
 */

const int max_skl_count[NUM_SKL_M + 1] = {
    -1,
    -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1,
    // ashiba(16) 1 次, zd(17) 1 次, Hither(18) 1 次
    1, 1, 1, -1, -1,
    -1, -1, -1, -1, -1,
    -1, -1, -1, 0, 0,
    -1
};
// clang-format on

std::vector<std::pair<int, SkillPack>> skillPack(
    const std::vector<std::pair<int, Skill>> &choices) {
    std::map<int, SkillPack> res;
    for (auto skl : choices) {
        auto &pid = skl.first;
        auto &skill = skl.second;
        if (res.count(pid) == 0) {
            // 不存在玩家对应的 SkillPack, 创建 SkillPack
            res[pid] = SkillPack();
        }
        res[pid].skills.push_back(skill);
    }
    std::vector<std::pair<int, SkillPack>> res1;
    for (auto player : res) {
        res1.push_back(std::make_pair(player.first, player.second));
    }
    return res1;
}

std::vector<std::pair<int, SkillPack>> clean_choices(
    const std::vector<std::pair<int, SkillPack>> &choices) {
    std::vector<std::pair<int, SkillPack>> res;
    res.clear();
    for (auto &player : choices) {
        if (tag_died[player.first] == true) {
            continue;
        }
        res.push_back(player);
    }
    return res;
}

// 记录上一批次的招数
std::map<int, std::map<skill, bool>> last_skill_used;

std::map<int, bool> do_main(
    const std::vector<std::pair<int, SkillPack>> &dirty_choices) {
    // Step 1: 清洗数据
    std::vector<std::pair<int, SkillPack>> choices =
        clean_choices(dirty_choices);

    // Step 2: 检查是否有空出招
    for (auto player : choices) {
        if (player.second.skills.size() < 1) {
            dprint("[Step 2] 玩家 " + std::to_string(player.first) +
                   " 没有任何出招但出现在参数中");
        }
    }

    // Step 2: 招式计数
    for (auto player : choices) {
        auto &pid = player.first;
        auto &psp = player.second;
        dprint("[Step 2] 招式计数, 玩家 " + std::to_string(pid));
        for (auto skl : psp.skills) {
            skl_count[pid][skl]++;
        }
    }

    // Step 2: 处理招式叠加是否允许
    for (auto player : choices) {
        auto &pid = player.first;
        auto &psp = player.second;

        // 扫描一遍招式叠加情况

        // 是否含有不可叠加的招式
        bool have_unoverlay = false;
        bool have_failed = false;
        bool have_overlay_group = false;
        std::string overlay_group_id = "";
        for (auto skl : psp.skills) {
            if (query_skill_can_overlay(skl) == false) {
                // 当前招式不允许叠加
                have_unoverlay = true;
                if (psp.skills.size() > 1) {
                    // 同时出的不同种类招式数 > 1 并且有不可叠加的招式时,
                    // 必不合法
                    dprint("[Step 2] 检测到不合法输入 (player: " +
                           std::to_string(pid) + "), 不同种类招式数:" +
                           std::to_string(psp.skills.size()) +
                           ", 不可叠加 skill_id:" + std::to_string(skl));
                    have_failed = true;
                    break;
                }
            } else {
                // 当前招式允许叠加
                std::string ogid = tskl::query_skill_overlay_name(skl);
                if (!have_overlay_group) {
                    have_overlay_group = true;
                    overlay_group_id = ogid;
                } else {
                    if (overlay_group_id != ogid) {
                        // 之前已有允许叠加的招式且叠加组 id 不一致
                        dprint("[Step 2] 检测到不合法输入 (player: " +
                               std::to_string(pid) +
                               "), 多个叠加组 id, 新 id:" + ogid +
                               ", 旧 id:" + overlay_group_id);
                        have_failed = true;
                        break;
                    }
                }
            }
        }
        dprint("[Step 2] 玩家 " + std::to_string(pid) + " " +
               (std::string)(have_unoverlay ? "有" : "没有") +
               "不可叠加的招式");
        if (have_failed) {
            dprint("[Step 2] 玩家 " + std::to_string(pid) + " " +
                   "不合法出招, 判死");
            tag_died[pid] = true;
        }
    }

    choices = clean_choices(choices);

    // Step 2: 处理不合法输出 (多次咕噜咕噜, 管类后出无关招式)
    for (auto player : choices) {
        auto &pid = player.first;
        auto &psp = player.second;
        assert(psp.skills.size() > 0);
        // 此处需要关注的招式: 咕噜咕噜, 管
        if (last_skill_used[pid][tskl::gulu] &&
            last_skill_used[pid][tskl::tube]) {
            // 两个都有时, 若先前的合法性判断正确, 只能为先出 gulu 再出 tube,
            // 故此处只能出 tube_selected
            for (auto skl : psp.skills) {
                if (skl != tskl::tube_selected) {
                    dprint("[Step 2] 玩家 " + std::to_string(pid) +
                           " 已使用了咕噜咕噜和管类, 但本次出了不合法招式: " +
                           std::to_string(skl) + "(" + get_skill_name(skl) +
                           "), 期待招式为管(已选择), 出局");
                    tag_died[pid] = true;
                }
            }
        } else if (last_skill_used[pid][tskl::tube]) {
            for (auto skl : psp.skills) {
                if (skl != tskl::tube_selected) {
                    dprint("[Step 2] 玩家 " + std::to_string(pid) +
                           " 已使用了管类, 但本次出了不合法招式: " +
                           std::to_string(skl) + "(" + get_skill_name(skl) +
                           "), 期待招式为管(已选择), 出局");
                    tag_died[pid] = true;
                }
            }
        } else if (last_skill_used[pid][tskl::gulu]) {
            for (auto skl : psp.skills) {
                if (skl == tskl::gulu) {
                    dprint("[Step 2] 玩家 " + std::to_string(pid) +
                           " 已使用了咕噜咕噜, 但本次出了不合法招式: " +
                           std::to_string(skl) + "(" + get_skill_name(skl) +
                           "), 出局");
                    tag_died[pid] = true;
                }
            }
        }
    }

    choices = clean_choices(choices);

    // Step 2: 处理使用次数达到上限的情况
    for (auto player : choices) {
        auto &pid = player.first;
        auto &psp = player.second;
        for (auto skl : psp.skills) {
            int ncnt = skl_count[pid][skl];  // 现在已使用的
            int lcnt = max_skl_count[skl];   // 限制次数
            dprint("[Step 2] 玩家 " + std::to_string(pid) +
                       " 出招 id=" + std::to_string(skl) + ", 已使用 " +
                       std::to_string(ncnt) + " 次, ",
                   false);
            if (lcnt == -1) {
                // 该技能无限使用
                dprint("该招数无使用次数限制");
            } else {
                dprint("该招数限制使用 " + std::to_string(lcnt) + " 次, ",
                       false);
                if (ncnt <= lcnt) {
                    // 没有超出限制
                    dprint("没有超出限制");
                } else {
                    // 超出了限制
                    dprint("超出限制, 判死");
                    tag_died[pid] = true;
                    break;
                }
            }
        }
    }

    choices = clean_choices(choices);

    std::map<int, std::map<tskl::skill, bool>> player_have_skill;
    // Step 2: 处理爆气
    for (auto player : choices) {
        auto &pid = player.first;
        auto &psp = player.second;
        // 需要支出的气数
        int consume_qi = 0;
        for (auto skl : psp.skills) {
            // 遍历该玩家所出的每个招式
            consume_qi += skl_qi[skl];
            dprint("[Step 2] 玩家 " + std::to_string(pid) + " 出招 id=" +
                   std::to_string(skl) + ", 消耗 " + formatxstr(skl_qi[skl]));
            if (player_have_skill[pid][skl] == false) {
                // 玩家之前未出过该技能, 本次耗气添加 skl_qi_base
                consume_qi += skl_qi_base[skl];
                player_have_skill[pid][skl] = true;
                dprint("[Step 2] 玩家 " + std::to_string(pid) +
                       " 第一次出招 id=" + std::to_string(skl) + ", 消耗 " +
                       formatxstr(skl_qi_base[skl]));
            }
        }
        dprint("[Step 2] 玩家 " + std::to_string(pid) + " 所用的总气数为 " +
                   formatxstr(consume_qi) + " 当前有气数为 " +
                   formatxstr(qi[pid]) + ", ",
               false);
        if (consume_qi > qi[pid]) {
            // 爆气了
            dprint("爆气了, 处死");
            tag_died[pid] = true;
            continue;
        } else {
            // 没爆气
            qi[pid] -= consume_qi;
            dprint("没爆气, 还剩 " + formatxstr(qi[pid]));
        }
    }

    choices = clean_choices(choices);

    // Step 3: 若存在管类(tskl::tube)或者咕噜咕噜 (tskl::gulu) -> 函数结束,
    // 并等待下一次调用. (Step 3 后已经没有还未出招的延迟类技能)

    std::map<int, bool> tres;
    tres.clear();
    // 是否存在有延迟出招的玩家
    bool have_delayed = false;
    // 是否存在出评测的玩家
    bool have_judge = false;
    for (auto player : choices) {
        auto &pid = player.first;
        auto &psp = player.second;
        for (auto skl : psp.skills) {
            if (skl == tskl::judge) {
                dprint("[Step 3] 玩家 " + std::to_string(pid) + " 出招评测");
                have_judge = true;
            }
        }
    }
    for (auto player : choices) {
        auto &pid = player.first;
        auto &psp = player.second;
        tres[pid] = false;
        for (auto skl : psp.skills) {
            if (skl == tskl::tube || skl == tskl::gulu) {
                // 存在管类或者咕噜咕噜
                dprint("[Step 3] 玩家 " + std::to_string(pid) + " 出招 id=" +
                       std::to_string(skl) + " 为" + tskl::get_skill_name(skl));
                if (have_judge && skl == tskl::gulu) {
                    dprint("[Step 3] 玩家 " + std::to_string(pid) +
                           " 被评测出局");
                    tag_died[pid] = true;
                    tres[pid] = false;
                } else {
                    tres[pid] = true;
                    have_delayed = true;
                }
            }
        }
    }

    // Step 2: 招式使用记录
    for (auto player : choices) {
        auto &pid = player.first;
        auto &psp = player.second;
        for (auto skl : psp.skills) {
            if (!last_skill_used[pid][skl]) {
                dprint("[Step 2] 招式使用记录: 玩家 " + std::to_string(pid) +
                       ", 招式: " + std::to_string(skl) + " (" +
                       get_skill_name(skl) + ")");
                last_skill_used[pid][skl] = true;
            }
        }
    }

    if (have_delayed) {
        // Step 3 返回前: 为所有已出局玩家的气数清零
        for (auto player : *players) {
            auto &pid = player;
            if (tag_died[pid]) {
                qi[pid] = 0;
                dprint("[Step 3*] 玩家 " + std::to_string(pid) +
                       " 已死亡, 气数清零");
            }
        }
        dprint("[Step 3] 存在需要延迟出招的玩家, 函数结束, 等待下一次调用");
        return tres;
    }

    choices = clean_choices(choices);

    // Step 4: 计算直接出局类:
    // 如果场上有人出拍气(tskl::clap)或者夹剑(tskl::fetch_sword),
    // 那么出木稿的玩家出局.

    bool have_out = false;  // 是否有直接出局类型
    for (auto player : choices) {
        auto &pid = player.first;
        auto &psp = player.second;
        for (auto skl : psp.skills) {
            if (skl == tskl::clap || skl == tskl::fetch_sword) {
                // 存在直接出局类
                dprint("[Step 4] 玩家 " + std::to_string(pid) +
                       " 出招 id=" + std::to_string(skl) + " 为直接出局类");
                have_out = true;
#ifndef debug
                break;  // 非调试模式下直接跳出
#endif
            }
        }
    }
    if (have_out) {
        for (auto player : choices) {
            auto &pid = player.first;
            auto &psp = player.second;
            for (auto skl : psp.skills) {
                if (skl == tskl::wooden_axe) {
                    // 出木稿
                    dprint("[Step 4] 玩家 " + std::to_string(pid) +
                           " 出了木镐, 出局");
                    tag_died[pid] = true;
                }
            }
        }
    }

    // Step 4.5: 展开 Hither, Alpaca

    std::vector<std::pair<int, SkillPack>> flatten_choices;
    for (auto player : choices) {
        auto &pid = player.first;
        auto &psp = player.second;
        auto flatten_pack = SkillPack();  // 展开后的 SkillPack
        for (auto skl : psp.skills) {
            if (skl != tskl::hither && skl != tskl::alpaca) {
                flatten_pack.skills.push_back(
                    skl);  // 无关的 Skill 原封不动拷贝
                continue;
            }
            dprint("[Step 4.5] 玩家 " + std::to_string(pid) +
                   " 出对群招式 (id=" + std::to_string(skl) + ")");
            // Hither/Alpaca 的展开
            // 此处原来的 Skill 中 Hither/Alpaca 的 target 并无实际含义
            // (都是对群技能)

            // 枚举其他玩家
            for (auto player : choices) {
                if (player.first == pid) continue;
                flatten_pack.skills.push_back(Skill(skl, player.first));
                dprint("[Step 4.5] 展开技能: " + std::to_string(pid) + " -> " +
                       std::to_string(player.first));
            }
        }
        // 将 flattern_pack 覆盖原来的 SkillPack
        flatten_choices.push_back(std::make_pair(pid, flatten_pack));
    }
    choices = flatten_choices;

    choices = clean_choices(choices);

    // Step 5: 计算每名玩家的防御上下限 (注意攻击招数所带来的防御不算在内,
    // 使用方法检查出招是否为攻击招数).
    int def_lower_bound[MAX_PLAYER_NUM + 1],
        def_upper_bound[MAX_PLAYER_NUM + 1];
    // 初始化数组
    for (int i = 0; i <= player_num; i++) {
        def_lower_bound[i] = def_upper_bound[i] = 0;
    }
    for (auto player : choices) {
        auto &pid = player.first;
        auto &psp = player.second;
        int def_lower = 0, def_upper = 0;  // 防御上下限
        for (auto skl : psp.skills) {
            def_lower += skl_min_defense[skl];
            def_upper += skl_max_defense[skl];
        }
        dprint("[Step 5] 玩家 " + std::to_string(pid) + " 的防御上下限分别为 " +
                   formatxstr(def_lower) + " 和 " + formatxstr(def_upper),
               false);
        if (def_lower > def_upper) {
            // 防御下限大于防御上限, 说明防御上限为 -1, 将其改为最大值
            dprint("防御下限大于防御上限, 将其改为最大值");
            def_upper = INT_MAX;
        } else {
            // 补齐换行
            dprint("", true);
        }
        // 将该玩家的防御上下限记录下来
        def_lower_bound[pid] = def_lower;
        def_upper_bound[pid] = def_upper;
    }

    choices = clean_choices(choices);

    // Step 6: 夹剑、夹拳、夹波波剑, 若夹成功, 因去除被夹的武器(或记为报废),
    // 并加气.
    auto destoryed_choices = choices;
    for (auto player : choices) {
        auto &pid = player.first;
        auto &psp = player.second;
        for (auto skl : psp.skills) {
            auto &skill = skl.skl;
            auto &target = skl.target;
            if (target == pid) {
                dprint("[Step 6] 警告: 玩家 " + std::to_string(pid) +
                       " 出招 id=" + std::to_string(skill) + +", 目标为自身");
            }
            if (skill != tskl::fetch_sword && skill != tskl::fetch_bo &&
                skill != tskl::fetch_fist)
                continue;
            dprint("[Step 6] 玩家 " + std::to_string(pid) + " 对 " +
                       std::to_string(target) + " 出夹类, ",
                   false);

            int wooden_sword_cnt = 0;
            int yellow_sword_cnt = 0;
            int bo_sword_cnt = 0;
            int fist_cnt = 0;
            int delta = 0;
            switch (skill) {
                case tskl::fetch_sword:
                    wooden_sword_cnt = get_player_skill_num(choices, target,
                                                            tskl::wooden_sword);
                    yellow_sword_cnt = get_player_skill_num(choices, target,
                                                            tskl::yellow_sword);
                    dprint("夹剑: 木剑 " + std::to_string(wooden_sword_cnt) +
                               " 个, 黄剑 " + std::to_string(yellow_sword_cnt) +
                               " 个, ",
                           false);
                    delta = int(0.5 * 100) + wooden_sword_cnt * 1 * 100 +
                            yellow_sword_cnt * int(2.5 * 100);
                    qi[pid] += delta;
                    dprint("加气 " + formatxstr(delta));
                    destoryed_choices = strip_player_skill(
                        destoryed_choices, target, tskl::wooden_sword);
                    destoryed_choices = strip_player_skill(
                        destoryed_choices, target, tskl::yellow_sword);
                    break;
                case tskl::fetch_fist:
                    fist_cnt =
                        get_player_skill_num(choices, target, tskl::fist);
                    dprint("夹拳: " + std::to_string(fist_cnt) + " 个, ");
                    delta = int(0.5 * 100);  // 此处加分规则存疑
                    qi[pid] += delta;
                    dprint("加气 " + formatxstr(delta));
                    destoryed_choices = strip_player_skill(destoryed_choices,
                                                           target, tskl::fist);
                    break;
                case tskl::fetch_bo:
                    bo_sword_cnt =
                        get_player_skill_num(choices, target, tskl::bo_sword);
                    dprint("夹波波剑: " + std::to_string(bo_sword_cnt) +
                           " 个, ");
                    delta = int(0.5 * 100) + bo_sword_cnt * 3 * 100;
                    qi[pid] += delta;
                    dprint("加气 " + formatxstr(delta));
                    destoryed_choices = strip_player_skill(
                        destoryed_choices, target, tskl::bo_sword);
                    break;
                default:
                    dprint("");
                    dprint("[Step 6] 警告: 执行到了不可达区域");
                    assert(false);
                    break;
            }
        }
    }
    choices = destoryed_choices;

    choices = clean_choices(choices);

    // Step 7: 计算每位玩家收到的伤害 (估计时间复杂度 O(n^2)),
    // 对于每个点对点的玩家判定伤害的过程, 对于出招为攻击类的玩家,
    // 为该玩家添加一个盾, 其盾量等于这位玩家对于对手的攻击量,
    // 之后计算并出局不能承受伤害的玩家.

    // 当前的招式设计中玩家获得盾为以下方式中的其一:
    // (1) 群盾: eg. defense, mid_defense, 换气类. 这种盾对所有玩家有效,
    // 受到伤害时减去相应盾量, 直到盾量不足以抵消受攻击量时破盾, 玩家出局 /
    // 镐破. (2) 单盾: eg. 部分攻击类. 这种盾对攻击者只对被攻击者有效
    // (即使该招式是对群招式 eg. alpaca), 玩家之间单对单结算盾量和受攻击量.
    // 当单盾的盾量不足抵抗时, 可以用群盾抵消其余未抵消的受攻击量.
    // (目前未出现这种情况)

    std::map<int, std::map<int, int>> player_get_damage;
    player_get_damage.clear();
    std::map<int, std::map<int, int>> player_do_attack;
    player_do_attack.clear();
    // 初始化数组
    for (auto player : choices) {
        auto &pid = player.first;
        auto &psp = player.second;
        for (auto skl : psp.skills) {
            if (query_skill_is_attack(skl)) {
                auto &target = skl.target;
                // 该招是攻击招式
                dprint("[Step 7] 玩家 " + std::to_string(pid) +
                           " 出招 id=" + std::to_string(skl) +
                           " 为攻击类, 对玩家 " + std::to_string(target) + ", ",
                       false);
                if (target == pid) {
                    dprint("检测到玩家 " + std::to_string(pid) +
                           " 的攻击对象为自己, 跳过");
                    continue;
                }
                if (tag_died[target]) {
                    // 对手已经出局
                    dprint("对手已经出局, 跳过");
                    continue;
                }
                dprint("");
                dprint("[Step 7] 玩家 " + std::to_string(pid) + " 对玩家 " +
                       std::to_string(target) + " 造成了 " +
                       formatxstr(skl_attack[skl]) + " 点伤害, 建立单盾");
                // 对该玩家造成了伤害
                player_do_attack[pid][target] += skl_attack[skl];
                player_get_damage[target][pid] += skl_attack[skl];
            }
        }
    }

    // Step 8: 计算反弹: 对于每个带有反弹招式的玩家, 减免受伤害玩家的伤害,
    // 并转换为对发起方的伤害.

    choices = clean_choices(choices);

    // Step 9: 对于一个玩家, 除了可能受到反弹回来的伤害,
    // 还会受到其他玩家的普通形式的攻击伤害, 将这些伤害叠加,
    // 出局不能承受伤害的玩家.
    for (auto player : choices) {
        auto &pid = player.first;
        for (auto damage_pair : player_get_damage[pid]) {
            if (tag_died[pid]) break;
            auto &owner = damage_pair.first;
            auto &value = damage_pair.second;
            auto &attack = player_do_attack[pid][owner];
            dprint("[Step 9] 玩家 " + std::to_string(pid) + " 受到玩家 " +
                       std::to_string(owner) + " 的 " + formatxstr(value) +
                       " 点攻击, 当前玩家发出对单攻击量为 " +
                       formatxstr(attack) + ", 对群防御值为 " +
                       (def_upper_bound[pid] == -1
                            ? "无限"
                            : ("[" + formatxstr(def_lower_bound[pid]) + ", " +
                               formatxstr(def_upper_bound[pid]) + "]") +
                                  ", "),
                   false);

            if (value <= attack) {
                // 单盾可以抵抗
                dprint("单盾抵抗");
                // 后面不会再用到 player_get_damage, player_do_attack, 不再修改
            } else if (def_upper_bound[pid] == -1) {
                dprint("无限群盾抵抗");
            } else {
                dprint("需要使用群盾", false);
                int delta = value - attack;  // 需要再群盾中扣除的部分
                def_upper_bound[pid] = def_upper_bound[pid] - delta;
                def_lower_bound[pid] = def_lower_bound[pid] - delta;
                if (def_upper_bound[pid] < 0) {
                    dprint("无法抵抗, 出局");
                    tag_died[pid] = true;
                    continue;
                } else {
                    dprint("可以抵抗, 剩余 [" +
                           formatxstr(def_lower_bound[pid]) + ", " +
                           formatxstr(def_upper_bound[pid]) + "]");
                }
            }
        }
        // 处理受到伤害未达到盾下限的情况
        if (def_lower_bound[pid] > 0) {
            dprint("[Step 9] 玩家 " + std::to_string(pid) +
                   " 未达到群盾下限, 剩余 " + formatxstr(def_lower_bound[pid]) +
                   ", 出局");
            tag_died[pid] = true;
            continue;
        }
    }

    // Step 10: 破镐: 对于镐子, 钻镐, 附魔钻镐的出招者:
    // 受伤害数=最大防御数时, 镐子报废, 失去加气的功能.

    choices = clean_choices(choices);

    // Step 11: 黄剑判定, 受黄剑攻击者未出局, 则出黄剑者出局,
    // 注意黄剑的连锁判定情况.

    for (auto player : choices) {
        auto &pid = player.first;
        auto &psp = player.second;
        for (auto skl : psp.skills) {
            auto &target = skl.target;
            if (skl == tskl::yellow_sword ||
                skl == tskl::yellow_sword_destoryed) {
                dprint("[Step 11] 玩家 " + std::to_string(pid) +
                           " 出黄剑, 对手 " + std::to_string(target) + " ",
                       false);
                if (tag_died[target]) {
                    dprint("已出局");
                } else {
                    tag_died[pid] = true;
                    dprint("未出局, 该玩家出局");
                }
            }
        }
    }

    choices = clean_choices(choices);

    // Step 12: 镐子加气, 拍手加气.
    for (auto player : choices) {
        auto &pid = player.first;
        auto &psp = player.second;
        for (auto skl : psp.skills) {
            if (skl == tskl::clap || skl == tskl::wooden_axe ||
                skl == tskl::normal_axe || skl == tskl::diamond_axe ||
                skl == tskl::enchanted_axe) {
                dprint("[Step 12] 玩家 " + std::to_string(pid) +
                           " 出镐类或拍气类, ",
                       false);
                if ((skl == tskl::normal_axe || skl == tskl::diamond_axe ||
                     skl == tskl::enchanted_axe) &&
                    def_upper_bound[pid] == 0) {
                    // 镐子破了
                    dprint("受到攻击等于盾值, 镐子破");
                } else {
                    qi[pid] += skl_qi_add[skl];
                    dprint("加气 " + formatxstr(skl_qi_add[skl]) + ", 现在有 " +
                           formatxstr(qi[pid]));
                }
            }
        }
    }

    choices = clean_choices(choices);

    // Step 13: 为所有已出局玩家的气数清零
    for (auto player : *players) {
        auto &pid = player;
        if (tag_died[pid]) {
            qi[pid] = 0;
            dprint("[Step 13] 玩家 " + std::to_string(pid) +
                   " 已死亡, 气数清零");
        }
    }

    // Step 14: 构造返回值
    std::map<int, bool> res;
    res.clear();
    for (auto player : *players) {
        res[player] = false;
    }
    return res;
}
#else

// do_main：主小局判定程序
// choices: player_id, skill
void do_main(const std::vector<std::pair<int, Skill>> &dirty_choices) {
    //// 定义区域 - 开始
    std::map<int, float> qi_add;  // id -> qi
    // qi_add: 记录当前小局该玩家应得的气数, 但未加到计数器
    qi_add.clear();

    std::vector<std::pair<int, Skill>> choices = clean_choices(dirty_choices);

    //// 定义区域 - 结束

    // Step 0. 出招合法性
    bool has_died_er = false;  // 是否已死人
    for (const auto &player_choice : choices) {
        if (check_available(player_choice) == false) {
            // 不合法
            tag_died[player_choice.first] = true;
            has_died_er = true;
            dprint("[Step 0] 玩家 " + std::to_string(player_choice.first) +
                   " 检测出招不合法, tag_died 设为 true");
        }
    }
    dprint("[Step 0] 完成, has_died = ", false);
    if (has_died_er == true) {
#ifndef debug
        choices = clean_choices(choices);
#endif
        dprint("true");
    } else {
        dprint("false");
    }

    // Step 0.5. 添加计数器
    // 合法性检查通过, 将玩家选择的招式加入计数器
    for (const auto &player : choices) {
#ifndef debug
        assert(tag_died[player.first] == false);
#endif
        skl_count[player.first][player.second.skl]++;
        dprint("[Step 0.5] 玩家 " + std::to_string(player.first) + " 技能为 " +
               std::to_string(player.second.skl));
    }

    // Step 1. 处理拍气

    // 当前小局中是否有人拍气, 用于木镐判定
    bool has_clap = false;

    for (const auto &player_choice : choices) {
        assert(tag_died[player_choice.first] !=
               true);  // 理论上来说 choice 没有已死亡玩家了
        if (tag_died[player_choice.first] == true) {
            dprint("[Step 1] 玩家 " + std::to_string(player_choice.first) +
                   " 已死亡, 跳过");
        }
        /*
        if (tag_died[player_choice.first] == true) {
            dprint("[Step 1] 玩家 " + std::to_string(player_choice.first) + "
        已死亡, 跳过"); continue;
        }
         */
        if (player_choice.second.skl == clap) {
            dprint("[Step 1] 玩家 " + std::to_string(player_choice.first) +
                   " 出 clap, qi_add++");
            qi_add[player_choice.first]++;
            has_clap = true;
        }
    }

    // Step 2. 拍气导致木镐触发判定
    bool has_died_wooden_axe = false;
    if (has_clap == true) {
        dprint("[Step 2] 存在 Clap, 进入判定");
        for (const auto &player_choice : choices) {
            dprint(
                "[Step 2] 玩家 " + std::to_string(player_choice.first) + ": ",
                false);
            if (player_choice.second.skl == wooden_axe) {
                tag_died[player_choice.first] = true;
                has_died_wooden_axe = true;
                dprint("出木镐, 判死");
            } else {
                dprint("跳过");
            }
        }
    } else {
        dprint("[Step 2] 不存在 Clap, 跳过");
    }
    dprint("[Step 2] 完成, has died = ", false);
    if (has_died_wooden_axe == true) {
#ifndef debug
        choices = clean_choices(choices);
#endif
        dprint("true");
    } else {
        dprint("false");
    }

#ifdef STEP_3_USE_OLD
    // Step 3. 对于每两个不同的玩家之间进行对决判定
    bool has_died_in_att = false;
    // axe_lose: 标记玩家是否有镐类等值爆现象
    std::map<int, bool> axe_lose;
    axe_lose.clear();
    // has_died_in_att: 是否有人在对决阶段死去, 用于剪枝
    for (const auto &player1 : choices) {
        if (tag_died[player1.first] == true) {
            dprint("[Step 3] P1 = " + std::to_string(player1.first) +
                   ", 已死亡, 跳过");
            // player1 已经死了
            continue;
        }
        for (const auto &player2 : choices) {
            dprint("[Step 3] P1 = " + std::to_string(player1.first) +
                       ", P2 = " + std::to_string(player2.first) + ": ",
                   false);
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
                dprint("P2(" + std::to_string(player2.first) +
                       ") 已经死亡, 跳过");
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

            // TODO: 当前并没有考虑多人围攻一人的情况 (单人可以防御,
            // 但叠加后超过防御最大值)
            //// 伤害判定 - 开始
            // 剩下的是有人拥有攻击类的情况
            std::pair<float, float> def1, def2;
            // def1, def2: 定义为当前 player1 和 player2 所拥有的防御值,
            // 下限与上限
            def1 = def2 = std::make_pair(0, 0);
            def1 = get_defense(player1.second.skl);
            def2 = get_skl_defense(player2.second.skl);
            dprint("[Step 3] \t获取玩家 " + std::to_string(player1.first) +
                   " 的防御值为 [" + std::to_string(def1.first) + ", " +
                   std::to_string(def1.second) + "], 玩家 " +
                   std::to_string(player2.first) + " 的防御值为 [" +
                   std::to_string(def2.first) + ", " +
                   std::to_string(def2.second) + "]");
            float att1, att2;
            // att1, att2: 定义为当前 player1 和 player2 所发出的攻击值
            // 只有当 target 命中时才有攻击
            att1 = get_attack(player1.second.skl) *
                   bool(player1.second.target == player2.first);
            att2 = get_skl_attack(player2.second.skl) *
                   bool(player2.second.target == player1.first);
            dprint("[Step 3] \t获取玩家 " + std::to_string(player1.first) +
                   " 的攻击值为 " + std::to_string(att1) + ", 玩家 " +
                   std::to_string(player2.first) + " 的攻击值为 " +
                   std::to_string(att2));
            if (def1.second == -1) {
                dprint("[Step 3] \t玩家 " + std::to_string(player1.first) +
                       " 具有无限防御, 跳过");
                // 玩家1 拥有无限防御, 双方无实际伤害, 伤害判定跳过
            } else if (def2.second == -1) {
                dprint("[Step 3] \t玩家 " + std::to_string(player2.first) +
                       " 具有无限防御, 跳过");
                // 玩家2 拥有无限防御, 双方无实际伤害, 伤害判定跳过
            } else {
                dprint("[Step 3] \t进入对战状态: ", false);
                if (att1 > att2) {
                    float dd = att1 - att2;
                    dprint(
                        "P1 攻击值大于 P2, 差值为 " + std::to_string(dd) + ", ",
                        false);
                    if (!((dd >= def2.first) && (dd <= def2.second))) {
                        tag_died[player2.first] = true;
                        has_died_in_att = true;
                        dprint("P2 被攻击致死", false);
                        // player2 被攻击致死
                    } else if (have_axe(player2)) {
                        dprint("检测到 P2 有镐类, ", false);
                        if (def2.second == dd) {
                            axe_lose[player2.first] = true;
                            dprint("P2 等值爆", false);
                        } else {
                            dprint("P2 镐类未爆", false);
                        }
                    }
                } else if (att1 < att2) {
                    float dd = att2 - att1;
                    dprint(
                        "P1 攻击值小于 P2, 差值为 " + std::to_string(dd) + ", ",
                        false);
                    if (!((dd >= def1.first) && (dd <= def1.second))) {
                        tag_died[player1.first] = true;
                        has_died_in_att = true;
                        dprint("P1 被攻击致死", false);
                        // player1 被攻击致死
                    } else if (have_axe(player1)) {
                        dprint("检测到 P1 有镐类, ", false);
                        if (def1.second == dd) {
                            axe_lose[player1.first] = true;
                            dprint("P1 等值爆", false);
                        } else {
                            dprint("P1 镐类未爆", false);
                        }
                    }
                } else {
                    dprint("[Step 3] \t双方抵消, 继续", false);
                    // 双方抵消, 游戏继续进行
                }
            }
            //// 伤害判定 - 结束

            dprint("");

            //// 黄剑判定部分 - 开始
            dprint("[Step 3] \t黄剑判定部分: 开始");
            bool tmp_make_1_died, tmp_make_2_died;
            // tmp_make_X_died: 标记因黄剑而死亡的玩家,
            // 而双方同时出黄剑时同时死, 因此死亡标记修改应在判定完成之后
            tmp_make_1_died = tmp_make_2_died = false;
            if (player1.second.skl == yellow_sword &&
                tag_died[player2.first] == false) {
                // player1 未能使用黄剑杀死 player2
                tmp_make_1_died = true;
                has_died_in_att = true;
                dprint("[Step 3] \tP1 出黄剑, P2 上阶段未死, P1 置死");
            }
            if (player2.second.skl == yellow_sword &&
                tag_died[player1.first] == false) {
                // player2 未能使用黄剑杀死 player1
                tmp_make_2_died = true;
                has_died_in_att = true;
                dprint("[Step 3] \tP2 出黄剑, P1 上阶段未死, P2 置死");
            }
            tag_died[player1.first] |= tmp_make_1_died;
            tag_died[player2.first] |= tmp_make_2_died;
            dprint(
                "[Step 3] \t更新死亡状态, P1(" + std::to_string(player1.first) +
                ") = " + (tag_died[player1.first] == true ? "true" : "false") +
                ", P2(" + std::to_string(player2.first) +
                ") = " + (tag_died[player2.first] == true ? "true" : "false"));
            dprint("[Step 3] \t黄剑判定部分: 结束");
            //// 黄剑判定部分 - 结束

            //// 剪枝优化部分 - 开始
            dprint("[Step 3] \t剪枝优化部分: 开始");
            if (tag_died[player1.first] == true) {
                // player1 已经判死, 第二层循环可以剪枝跳过
                dprint("[Step 3] \t此时 P1(" + std::to_string(player1.first) +
                       ") 已经死亡, break");
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
    } else {
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
    std::map<int, std::pair<float, float>> has_def;

    suffer_att.clear();
    has_def.clear();

    // Step 3.1: 累计玩家受到攻击, 获取玩家防御值
    int overallHither = 0;  // 全场累计 Hither 次数
    for (const auto &player : choices) {
        if (tag_died[player.first] == true) {
            // 死去的玩家不被考虑发出的攻击值
            continue;
        }
        has_def[player.first] = get_skl_defense(player.second.skl);
        dprint("[Step 3.1] 玩家 " + std::to_string(player.first) +
                   " 拥有防御值: [" +
                   std::to_string(has_def[player.first].first) + ", " +
                   std::to_string(has_def[player.first].second) + "], ",
               false);
        if (player.second.skl == hither) {
            // Hither 特判
            overallHither++;
            dprint("发出 Hither");
        } else {
            suffer_att[player.second.target] +=
                get_skl_attack(player.second.skl);  // 该玩家的目标s
            dprint("发出攻击: " +
                   std::to_string(get_skl_attack(player.second.skl)) + " -> " +
                   "玩家 " + std::to_string(player.second.target));
        }
    }

    // Step 3.15: 处理 Hither
    dprint("[Step 3.15] 现有 Hither: " + std::to_string(overallHither));
    for (const auto &player : choices) {
        if (player.second.skl == hither) {
            dprint("[Step 3.15] 玩家 " + std::to_string(player.first) +
                   " 有 Hither, 受到攻击: " +
                   std::to_string(float(overallHither - 1) *
                                  get_skl_attack(hither)));
            suffer_att[player.first] +=
                float(overallHither - 1) * get_skl_attack(hither);
        } else {
            dprint(
                "[Step 3.15] 玩家 " + std::to_string(player.first) +
                " 没有 Hither, 受到攻击: " +
                std::to_string(float(overallHither) * get_skl_attack(hither)));
            suffer_att[player.first] +=
                (float)overallHither * get_skl_attack(hither);
        }
    }
    for (const auto &player : choices) {
        dprint("[Step 3.1] 玩家 " + std::to_string(player.first) +
               " 受到攻击: " + std::to_string(suffer_att[player.first]));
    }

    // Step 3.2: 攻击-防御对抗
    for (const auto &player : choices) {
        if (suffer_att[player.first] == 0) {
            dprint("[Step 3.2] 玩家 " + std::to_string(player.first) +
                   " 没有受到攻击");
            continue;
        }
        if ((suffer_att[player.first] >= has_def[player.first].first) &&
            suffer_att[player.first] <= has_def[player.first].second) {
            dprint(
                "[Step 3.2] 玩家 " + std::to_string(player.first) + " 可以防, ",
                false);
            // 可以防得住
            if (have_axe(player)) {
                dprint("有镐子, ", false);
                if (has_def[player.first].second == suffer_att[player.first]) {
                    // 有镐子且等值爆
                    axe_lose[player.first] = true;
                    dprint("等值爆");
                } else {
                    dprint("不爆");
                }
            } else {
                dprint("无镐子");
            }
        } else {
            // 防不住
            dprint("[Step 3.2] 玩家 " + std::to_string(player.first) +
                   " 不可防, 置死");
            tag_died[player.first] = true;
            has_died_in_att = true;
        }
    }
    // Step 3.3: 黄剑判定
    for (const auto &player : choices) {
        if (player.second.skl == yellow_sword) {
            // 有黄剑
            if (tag_died[player.second.target] == true) {
                // 攻击对象已死
                continue;
            } else {
                // 攻击对象未死, 自己死
                dprint("[Step 3.3] 玩家 " + std::to_string(player.first) +
                       " 出黄剑, 对象为 " +
                       std::to_string(player.second.target) +
                       ", 判定失败, 置死");
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
    for (const auto &player : choices) {
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
        } else {
            dprint("玩家出镐类, ", false);
            // 剩余的为镐类, Step 0 中已经处理了爆气的情况,
            // 所以不需要判断是否会爆气
            if (axe_lose[player.first]) {
                dprint("在上阶段等值爆, 不加气");
                continue;
            }
            // ps: 对玩家 skl 的临时引用
            const int &ps = player.second.skl;
            // id: 对玩家 first 的临时引用
            const int &id = player.first;
            if (ps == wooden_axe) {
                qi_add[id] += 3;
                dprint("+3");
            } else if (ps == normal_axe) {
                qi_add[id] += 4;
                dprint("+4");
            } else if (ps == diamond_axe) {
                qi_add[id] += 6;
                dprint("+6");
            } else if (ps == enchanted_axe) {
                qi_add[id] += 12;
                dprint("+12s");
            } else {
                // 未知错误
                assert(false);
            }
        }
    }

    // Step 5. qi_add -> qi, 处理 skill 扣气
    for (auto &player : choices) {
        if (tag_died[player.first] == true) {
            dprint("[Step 5] 玩家 " + std::to_string(player.first) +
                   " 已死亡, 跳过扣气");
            continue;
        }
        qi_add[player.first] -= skl_qi[player.second.skl];
        dprint("[Step 5] 玩家 " + std::to_string(player.first) + " 出招 " +
               std::to_string(player.second.skl) + ", 扣气 " +
               std::to_string(skl_qi[player.second.skl]) +
               ", qi_add = " + std::to_string(qi_add[player.first]));
    }
    for (auto player : *players) {
        if (qi_add[player] == 0) {
            dprint("[Step 5] 玩家 " + std::to_string(player) +
                   " 无加气, 现有气数为 " + std::to_string(qi[player]));
            continue;
        }
        qi[player] += qi_add[player];
        dprint("[Step 5] 玩家 " + std::to_string(player) +
               " 加气结算: delta 为 " + std::to_string(qi_add[player]) +
               ", 现有气数为 " + std::to_string(qi[player]));
    }

    // Step 6. 死去玩家 qi = 0
    for (auto player : *players) {
        if (tag_died[player] == true) {
            qi[player] = 0;
            dprint("[Step 6] 玩家 " + std::to_string(player) +
                   " 已死去, 气置 0");
        }
    }
}
#endif

void pretty_print_result_died(const std::vector<int> &_id,
                              const std::map<int, bool> &_tag_died,
                              const std::string &comment) {
    std::cout << "------- Died Players";
    if (comment != "") {
        std::cout << " - " << comment;
    }
    std::cout << " -------";
    std::cout << std::endl;
    bool flag = false;  // 记录是否输出过已经死去的玩家 id
    for (auto player : _id) {
        if (_tag_died.at(player) == false) continue;
        std::cout << player << "\t";
        flag = true;
    }
    if (flag == false) {
        std::cout << "Empty!";
    }
    std::cout << std::endl;
}

void pretty_print_result_qi(const std::vector<int> &_id,
                            const std::map<int, int> &_qi,
                            const std::string &comment) {
    std::cout << "------- Qi of Players";
    if (comment != "") {
        std::cout << " - " << comment;
    }
    std::cout << " -------";
    std::cout << std::endl;
    for (auto player : _id) {
        std::cout << player << "\t";
    }
    std::cout << std::endl;
    for (auto player : _id) {
        std::cout << formatxstr(_qi.at(player)) << "\t";
    }
    std::cout << std::endl;
}

game_status continue_game(int n, game_status now,
                          const std::vector<std::pair<int, Skill>> &choices) {
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
    for (auto player : *players) {
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
    for (auto player : *players) {
        dprint(std::to_string(player) + "\t", false);
    }
    dprint("", true);
    for (auto player : *players) {
        dprint(std::to_string(changed.qi[player]) + "\t", false);
    }
    dprint("", true);
    return changed;
}

// 编译环境: C++11
#endif  // WOODEN_JUDGE_CPP