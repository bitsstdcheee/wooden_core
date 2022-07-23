#include <cstdio>
#include <exception>
#include <iostream>
#include <new>
#include <ostream>
#include <stdlib.h>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>
#include <map>
#include <cassert>

#include "wooden_test.h"

// using namespace std;

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
std::map<int, std::map<int, int>> skl_count;

//dprint: debug 输出
void dprint(const std::string &msg, bool need_endl = true) {
    #ifdef debug
    std::cout << msg << std::endl;
    #endif
}

//dprint: debug 输出
void dprint(const char* msg, bool need_endl = true) {
    #ifdef debug
    std::cout << msg << std::endl;
    #endif
}


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

// 暂时不支持多选 skill
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


// Skill: 带有对象的招术封装
struct Skill {  
    skill skl;
    int target;
    // 显式转换 Skill -> skill
    operator skill() {
        // 无招术, 自动转换
        return skl;
    }
    Skill() {
        skl = none;
        target = 0;
    }
    Skill(skill _skl, int _target) {
        skl = _skl;
        target = _target;
    }
    Skill(test::skill _skl, int _target) {
        skl = skill(_skl);
        target = _target;
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

// clean_choices: 清洗玩家选择: 对于已死去的玩家的技能清除
std::vector<std::pair<int, Skill>> clean_choices(const std::vector<std::pair<int, Skill>> &choices) {
    std::vector<std::pair<int, Skill>> res;
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
const float maxd[] = {0, 
    0, 0, 0.5, 1, 2.5, 
    1, 2.5, 2, 3, 4, 
    5, 6, 3, 5, 6, 
    5, -1  // -1 为无限
};

// mind: 记录 skill 对应防御的最小值
const float mind[] = {0,
    0, 0, 0, 0, 0,
    0, 0, 0, 0, 0,
    0, 0, 0, 1, 1,
    0, 0
};

// attk: 记录 skill 对应攻击
const float attk[] = {0,
    0, 0, 0, 0, 0,
    1, 2.5, 2, 3, 4,
    5, 6, 0, 0, 0,
    0, 0
};

// sklqi: 记录 skill 对应使用的气数
const float sklqi[] = {0,
    0, 1, 2, 3, 6,
    1, 1, 2, 3, 4,
    5, 6, 0, 0, 0,
    0, 0
};

std::pair<float, float> get_defense(const skill &skl) {
    // get_defense: 获取并返回 skl 对应拥有的防御值
    return std::make_pair(mind[skl], maxd[skl]);
}

float get_attack(const skill &skl) {
    // get_attack: 获取并返回 skl 对应拥有的攻击值
    return attk[skl];
}

bool check_available(const std::pair<int, Skill> &choice) {
    // check_available: 检查当前玩家的选择是否合法 (爆气, 超出次数限制)
    // 返回值:
    // false: 不合法
    // true: 合法
    if (qi[choice.first] < sklqi[choice.second.skl]) return false;
    Skill cskl = choice.second;
    int id = choice.first;
    if (cskl == ashiba && skl_count[id][cskl.skl] >= 2) {
        // ashiba 阿西巴 每小局限制 2 次
        return false;
    } 
    if (cskl == zd && skl_count[id][cskl.skl] >= 1) {
        // 泽东 每小局限制 1 次
        return false;
    }
    return true;
}


void do_main(const std::vector<std::pair<int, Skill>> &dirty_choices) {
    // do_main：主小局判定程序
    // choices: player_id, skill

    //// 定义区域 - 开始
    std::map<int, float> qi_add; // id -> qi
    // qi_add: 记录当前小局该玩家应得的气数, 但未加到计数器
    qi_add.clear();

    std::vector<std::pair<int, Skill>> choices = clean_choices(dirty_choices);

    //// 定义区域 - 结束

    // Step 0. 出招合法性
    bool has_died_er = false;
    for (const auto & player_choice: choices) {
        if (check_available(player_choice) == false) {
            // 不合法
            tag_died[player_choice.first] = true;
            has_died_er = true;
            dprint("[Step 0] 玩家 " + std::to_string(player_choice.first) + " 检测出招不合法, tag_died 设为 true");
        } 
    }
    if (has_died_er == true) {
        choices = clean_choices(choices);
    }

    // Step 0.5. 添加计数器
    // 合法性检查通过, 将玩家选择的招式加入计数器
    for (const auto & player: choices) {
        assert(tag_died[player.first] == false);
        skl_count[player.first][player.second.skl] ++;
        dprint("[Step 0.5] 玩家 " + std::to_string(player.first) + " 技能为 " + std::to_string(player.second.skl));
    }

    // Step 1. 处理拍气
    bool has_clap = false;
    // 当前小局中是否有人拍气, 用于木镐判定
    for (const auto & player_choice : choices) {
        if (tag_died[player_choice.first] == true) {
            dprint("[Step 1] 玩家 " + std::to_string(player_choice.first) + " 已死亡, 跳过");
            continue;
        }
        if (player_choice.second.skl == clap) {
            dprint("[Step 1] 玩家 " + std::to_string(player_choice.first) + " 出 clap, qi_add++");
            qi_add[player_choice.first] ++;
            has_clap = true;
        }
    }

    // Step 2. 拍气导致木镐触发判定
    bool has_died_wooden_axe = false;
    if (has_clap == true) {
        for (const auto & player_choice: choices) {
            if (player_choice.second.skl == wooden_axe) {
                tag_died[player_choice.first] = true;
                has_died_wooden_axe = true;
            }
        }
    }
    if(has_died_wooden_axe == true) {
        choices = clean_choices(choices);
    }

    // Step 3. 对于每两个不同的玩家之间进行对决判定
    bool has_died_in_att = false;
    // has_died_in_att: 是否有人在对决阶段死去, 用于剪枝
    for (const auto & player1 : choices) {
        if (tag_died[player1.first] == true) {
            // player1 已经死了
            continue;
        }
        for (const auto & player2 : choices) {
            //// 初始剪枝 - 开始
            if (player1.first == player2.first) {
                // 相同的两个玩家, 跳过
                continue;
            }
            if (tag_died[player2.first == true]) {
                // player2 已经死了
                continue;
            }
            if (have_att(player1) == 0 && have_att(player2) == 0) {
                // 两人同时没有攻击类
                continue;
            }
            //// 初始剪枝 - 结束


            // TODO: 当前并没有考虑多人围攻一人的情况 (单人可以防御, 但叠加后超过防御最大值)
            //// 伤害判定 - 开始
            // 剩下的是有人拥有攻击类的情况
            std::pair<float, float> def1, def2;
            // def1, def2: 定义为当前 player1 和 player2 所拥有的防御值, 下限与上限
            def1 = def2 = std::make_pair(0, 0);
            def1 = get_defense(player1.second.skl);
            def2 = get_defense(player2.second.skl);
            float att1, att2;
            // att1, att2: 定义为当前 player1 和 player2 所发出的攻击值
            // 只有当 target 命中时才有攻击
            att1 = get_attack(player1.second.skl) * int(bool(player1.second.target == player2.first));
            att2 = get_attack(player2.second.skl) * int(bool(player2.second.target == player1.first));
            if (def1.second == -1) {
                // 玩家1 拥有无限防御, 双方无实际伤害, 伤害判定跳过
            }
            else if (def2.second == -1) {
                // 玩家2 拥有无限防御, 双方无实际伤害, 伤害判定跳过
            }
            else {
                if (att1 > att2) {
                    float dd = att1 - att2;
                    if (!((dd >= def2.first) && (dd <= def2.second))) {    
                        tag_died[player2.first] = true;
                        has_died_in_att = true;
                        // player2 被攻击致死
                    }
                }
                else if (att1 < att2) {
                    float dd = att2 - att1;
                    if (!((dd >= def1.first) && (dd <= def1.second))) {    
                        tag_died[player1.first] = true;
                        has_died_in_att = true;
                        // player1 被攻击致死
                    }
                }
                else {
                    // 双方抵消, 游戏继续进行
                }
            }
            //// 伤害判定 - 结束
            
            //// 黄剑判定部分 - 开始
            bool tmp_make_1_died, tmp_make_2_died;
            // tmp_make_X_died: 标记因黄剑而死亡的玩家, 而双方同时出黄剑时同时死,
            // 因此死亡标记修改应在判定完成之后
            tmp_make_1_died = tmp_make_2_died = false; 
            if (player1.second.skl == yellow_sword && tag_died[player2.first] == false) {
                // player1 未能使用黄剑杀死 player2
                tmp_make_1_died = true;
                has_died_in_att = true;
            }
            if (player2.second.skl == yellow_sword && tag_died[player1.first] == false) {
                // player2 未能使用黄剑杀死 player1
                tmp_make_2_died = true;
                has_died_in_att = true;
            }
            tag_died[player1.first] |= tmp_make_1_died;
            tag_died[player2.first] |= tmp_make_2_died;
            //// 黄剑判定部分 - 结束

            //// 剪枝优化部分 - 开始
            if (tag_died[player1.first] == true) {
                // player1 已经判死, 第二层循环可以剪枝跳过
                break;
            }
            //// 剪枝优化部分 - 结束
        }
    }
    if (has_died_in_att) {
        // 有玩家在这个步骤中死去, 清理
        choices = clean_choices(choices);
    }

    // TODO: 镐类等值爆
    // Step 4. 拍气, 镐子
    bool has_died_in_clap = false;
    for (const auto & player: choices) {
        if (tag_died[player.first]) {
            // player 已经死去
            continue;
        }
        if (have_clap_axe(player) == false) {
            // 玩家没有加气类招术
            continue;
        }
        if (player.second.skl == clap) {
            // qi_add[player.first] ++;
            // 这里在 Step 1 中已经加过气了, 不需要再加了
        }
        else {
            // 剩余的为镐类, Step 0 中已经处理了爆气的情况, 所以不需要判断是否会爆气 

            // ps: 对玩家 skl 的临时引用
            const int& ps = player.second.skl;
            // id: 对玩家 first 的临时引用
            const int& id = player.first;
            if (ps == wooden_axe) {
                qi_add[id] += 2;
            }
            else if (ps == normal_axe) {
                qi_add[id] += 2;
            }
            else if (ps == diamond_axe) {
                qi_add[id] += 3;
            }
            else if (ps == enchanted_axe) {
                qi_add[id] += 6;
            }
        }
    }

    // Step 5. qi_add -> qi
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

// pretty_print_result_died: 格式化打印玩家死亡信息
// _id: 玩家 id 列表
// _tag_died: 玩家死亡信息, 格式应与 tag_died 相同
// comment: 可选, 作为输出辅助信息
void pretty_print_result_died(const std::vector<int> &_id, const std::map<int, bool>& _tag_died, const std::string& comment = "") {
    std::cout << "--\tDied Players";
    if (comment != "") {
        std::cout << " - " << comment;
    }
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
    std::cout << "--\tQi of Players";
    if (comment != "") {
        std::cout << " - " << comment;
    }
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

// passon: 传递测试参数并运行测试的函数
void passon(const TESTN &test) {
    dprint("[P*] Entering passon()");
    const int &_player_num = test.player_num;
    assert(_player_num >= 2); // 玩家数量需大于或等于 2

    const std::vector<int> &_players = test.players;
    const std::map<int, float> &_qi = test.qi;
    const std::map<int, bool> &_tag_died = test.tag_died;
    const std::map<int, std::map<int, int>> &_skl_count = test.skl_count;
    const std::map<int, bool> &_res_tag_died = test.res_tag_died;
    const std::map<int, float> &_res_qi = test.res_qi;
    const std::map<int, test::skill> &_using_skill = test.using_skill;
    const std::map<int, int> &_target = test.target;

    // Step 0. 传入数据 -- 玩家个数断言
    dprint("[P0] Before importing data");
    assert(_players.size() == _player_num);
    assert(_qi.size() == _player_num);
    assert(_tag_died.size() == _player_num);
    assert(_skl_count.size() == _player_num);
    assert(_res_tag_died.size() == _player_num);
    assert(_res_qi.size() == _player_num);
    assert(_using_skill.size() == _player_num);
    assert(_target.size() == _player_num);

    // 转换 test::skill -> choices
    dprint("[P0] Before test::skill -> choices");
    auto* _dirty_choices = new std::vector<std::pair<int, Skill>>(_player_num);
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
    do_main(*_dirty_choices);
    dprint("[P2] After do_main()");

    // Step 2.5 打印结果
    pretty_print_result_died((*players), tag_died);
    pretty_print_result_qi((*players), qi);

    pretty_print_result_died((*players), _res_tag_died, "In test1");
    pretty_print_result_qi((*players), _res_qi, "In test1");
    dprint("[P2.5] After pretty printing");

    // Step 3. 判断结果
    // assert(_res_tag_died == tag_died);
    // assert(_res_qi == qi);
    dprint("[P3] Before assert result");
    assert(equal_map(*players, _res_tag_died, tag_died));
    assert(equal_map(*players, _res_qi, qi));
    
    std::cout << "Test success: " << test.comment << std::endl;
}

#define do_test(x) passon(test##x)

int main() {
    static_assert(sizeof(void *) == 8, "This program only support 64 bit.");
    assert(sizeof(void *) == 8); // 保证运行时的 64 位环境
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout << "This program was built on " << __DATE__ << ", " << __TIME__ << std::endl;
    // player_num = 5;
    // players = new std::vector<int>(player_num);  // 预分配空间

    // std::cout << player_num << std::endl;

    #ifdef ASSERT_TEST1
    do_test1_assert();
    #endif

    // std::map<int, bool> d1 = gen_map<int, bool>(4, {1, 2, 3, 4}, {false, false, false, false});
    do_test(3);
    
    return 0;
}

// 编译环境: C++11