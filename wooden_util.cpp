#ifndef WOODEN_UTIL_CPP
#define WOODEN_UTIL_CPP

#include "wooden_util.h"

using std::string;

const std::vector<int> gen_default_player(const int player_num) {
    auto* vec = new std::vector<int>(player_num);
    // vec->clear();
    for (int i = 0; i < player_num; i++) {
        (*vec)[i] = i + 1;
    }
    return *vec;
}

const std::map<int, int> gen_cleared_skl() {
    std::map<int, int> mp;
    mp.clear();
    for (int i = tskl::MIN_SKILL_NUM; i <= tskl::MAX_SKILL_NUM; i++) {
        mp[i] = 0;
    }
    return mp;
}

const std::map<int, bool> gen_all_alive(const std::vector<int>& players) {
    std::map<int, bool> mp;
    mp.clear();
    for (auto player : players) {
        mp[player] = false;
    }
    return mp;
}

const std::vector<int> gen_players(const int player_num) {
    return gen_default_player(player_num);
}

const std::map<int, int> gen_qi(const int player_cnt) {
    return gen_mapx<int, int>(player_cnt, gen_default_player(player_cnt), gen_repeated_vec<int>(0 * 100, player_cnt));
}

const std::map<int, int> gen_qi(std::initializer_list<int> qi, bool enable_x) {
    return enable_x ? gen_mapx<int, int>(qi.size(), gen_players(qi.size()), qi)
                    : gen_map<int, int>(qi.size(), gen_players(qi.size()), qi);
}

const std::map<int, int> gen_qi(std::initializer_list<int> players,
                                std::initializer_list<int> qi, bool enable_x) {
    assert(players.size() == qi.size());
    return enable_x ? gen_mapx<int, int>(players.size(), players, qi)
                    : gen_map<int, int>(players.size(), players, qi);
}

const std::map<int, bool> gen_tag_died(std::initializer_list<bool> tag_died) {
    return gen_map<int, bool>(tag_died.size(), gen_players(tag_died.size()),
                              tag_died);
}

const std::map<int, bool> gen_tag_died(const int player_num) {
    return gen_all_alive(gen_players(player_num));
}

const std::map<int, std::map<int, int> > gen_skl_count(
    std::initializer_list<std::map<int, int> > skl_count) {
    return gen_map<int, std::map<int, int> >(
        skl_count.size(), gen_players(skl_count.size()), skl_count);
}

const std::map<int, std::map<int, int> > gen_skl_count(const int player_num) {
    return gen_map<int, std::map<int, int> >(
        player_num, gen_players(player_num),
        gen_repeated_vec(gen_cleared_skl(), player_num));
}

const std::map<int, tskl::skill> gen_using_skill(
    std::initializer_list<tskl::skill> skill) {
    return gen_map<int, tskl::skill>(skill.size(), gen_players(skill.size()),
                                     skill);
}

const std::map<int, std::vector<tskl::skill> > gen_using_skill(
    std::map<int, std::vector<tskl::skill> > skill) {
    return skill;
}

const std::map<int, int> gen_target(std::initializer_list<int> target) {
    return gen_map<int, int>(target.size(), gen_players(target.size()), target);
}

const std::map<int, bool> gen_res_tag_died(
    std::initializer_list<bool> tag_died) {
    return gen_tag_died(tag_died);
}

const std::map<int, int> gen_res_qi(std::initializer_list<int> qi,
                                    bool enable_x) {
    return gen_qi(qi, enable_x);
}

RoundPatch::RoundPatch() {
    head = true;
    judged = false;
}

RoundPatch::RoundPatch(string _id, string _prev_patch, std::vector<int> _players, std::map<int, std::vector<Skill>> _choices, bool _head) {
    id = _id;
    prev_patch = _prev_patch;
    players = std::move(_players);
    choices = std::move(_choices);
    head = _head;
    judged = false;
    // 检查数量是否正确
    assert(players.size() == choices.size());
}

RoundPatch::RoundPatch(string _id, std::vector<int> _players, std::map<int, std::vector<Skill>> _choices, bool _head) {
    id = _id;
    players = std::move(_players);
    choices = std::move(_choices);
    head = _head;
    judged = false;
    // 检查数量是否正确
    assert(players.size() == choices.size());
}

RoundPatch::RoundPatch(string _id, string _prev_patch, std::vector<int> _players, std::map<int, std::vector<Skill>> _choices, std::map<int, int> _qi, std::map<int, bool> _tag_died, std::map<int, std::map<int, int>> _skl_count, std::map<int, std::map<tskl::skill, bool>> _last_skill_used, std::map<int, bool> _delayed_players, bool _head, std::vector<string> _next_patch) {
    id = _id;
    prev_patch = _prev_patch;
    next_patch = std::move(_next_patch);
    players = std::move(_players);
    qi = std::move(_qi);
    choices = std::move(_choices);
    tag_died = std::move(_tag_died);
    skl_count = std::move(_skl_count);
    last_skill_used = std::move(_last_skill_used);
    delayed_players = std::move(_delayed_players);
    head = _head;
    judged = true;
    // 不会检查数量是否正确
    /*
    assert(players.size() == qi.size());
    assert(players.size() == choices.size());
    assert(players.size() == tag_died.size());
    assert(players.size() == skl_count.size());
    assert(players.size() == last_skill_used.size());
    assert(players.size() >= delayed_players.size());
    */
}

bool RoundPatch::operator < (const RoundPatch x) const {
    return id < x.id;
}

// 调用 do_main 的函数, 直接将结果写入 RoundPatch
void judge_helper(std::vector<int>& _players, std::map<int, int>& _qi, std::map<int, bool> _tag_died, std::map<int, std::map<int, int>>& _skl_count, std::map<int, std::vector<Skill>>& _choices, RoundPatch& patch, std::map<int, std::map<tskl::skill, bool>> _last_skill_used = std::map<int, std::map<tskl::skill, bool>>()) {
    players = &_players;
    qi = _qi;
    tag_died = _tag_died;
    skl_count = _skl_count;
    last_skill_used = _last_skill_used;
    // 转换 choices
    std::vector<std::pair<int, SkillPack>> _choices_new;
    for (auto player : _choices) {
        auto& pid = player.first;
        auto& psp = player.second;
        SkillPack sp;
        for (auto skl : psp) {
            sp.skills.push_back(skl);
        }
        _choices_new.push_back(std::make_pair(pid, sp));
    }
    patch.delayed_players = do_main(_choices_new);
    patch.qi = qi;
    patch.tag_died = tag_died;
    patch.skl_count = skl_count;
    patch.skill_used = last_skill_used;
}

// 调用 do_main 的函数
// 返回 pair <延迟出招的玩家列表, 玩家上一次出招>
std::pair<std::map<int, bool>, std::map<int, std::map<tskl::skill, bool>>> judge_helper(std::vector<int>& _players, std::map<int, int>& _qi, std::map<int, bool> _tag_died, std::map<int, std::map<int, int>>& _skl_count, std::map<int, std::vector<Skill>>& _choices, std::map<int, std::map<tskl::skill, bool>> _last_skill_used = std::map<int, std::map<tskl::skill, bool>>()) {
    players = &_players;
    qi = _qi;
    tag_died = _tag_died;
    skl_count = _skl_count;
    last_skill_used = _last_skill_used;
    // 转换 choices
    std::vector<std::pair<int, SkillPack>> _choices_new;
    for (auto player : _choices) {
        auto& pid = player.first;
        auto& psp = player.second;
        SkillPack sp;
        for (auto skl : psp) {
            sp.skills.push_back(skl);
        }
        _choices_new.push_back(std::make_pair(pid, sp));
    }
    return std::make_pair(do_main(_choices_new), last_skill_used);
}

bool RoundPatch::judge(std::map<string, RoundPatch>* data) {
    if (this->judged) {
        // 已经计算过了
        return false;
    }
    if (prev_patch.empty()) {
        // 没有前驱记录 且 当前没有计算
        dprint("错误: 当前 ID=" + id + " 无前驱且尚未计算");
        return true;
        
    }
    if (data->find(prev_patch) == data->end()) {
        // 没有找到相关信息
        dprint("错误: 无法找到 ID=" + id + " 的前驱 ID=" + prev_patch + " 对应批次信息");
        return true;
    }
    auto& father = data->at(prev_patch);
    if (!father.judged) {
        if (father.judge(data)) return true;
    }
    /*
    assert(players.size() == father.players.size());
    assert(players.size() == father.qi.size());
    assert(players.size() == father.tag_died.size());
    assert(players.size() == father.skl_count.size());
    assert(players.size() >= father.skill_used.size());
    assert(players.size() >= father.delayed_players.size());
    */
    // 如果当前批次为小局的第一批次, 则不需要 last_skill_used 信息
    if (head)
        judge_helper(this->players, father.qi, father.tag_died, father.skl_count, this->choices, *this);
    else
        judge_helper(this->players, father.qi, father.tag_died, father.skl_count, choices, *this, father.skill_used);
    this->judged = true;
    return false;
}

void print_single_skill(const Skill &skl, bool need_endl) {
    Skill tmp = skl;
    dprint("[" + tskl::get_skill_name(tmp) + " > " +
               std::to_string(skl.target) + "]",
           need_endl);
}

void print_batch(const std::map<int, std::vector<Skill>> &batch, std::string name, std::string line_prefix,
int len_offset, bool print_header) {
    // 转换 batch
    std::vector<std::pair<int, SkillPack>> _batch_new;
    for (auto player : batch) {
        auto& pid = player.first;
        auto& psp = player.second;
        SkillPack sp;
        for (auto skl : psp) {
            sp.skills.push_back(skl);
        }
        _batch_new.push_back(std::make_pair(pid, sp));
    }
    print_batch(_batch_new, name, line_prefix, len_offset, print_header);
}

void print_batch(const std::vector<std::pair<int, SkillPack> > &batch,
                 std::string name, std::string line_prefix,
                 int len_offset, bool print_header) {
    if (print_header) dprint(line_prefix + "###### " + (name == "" ? "轮次" : name) + " ######");
    for (auto choice : batch) {
        auto &pid = choice.first;
        auto &psp = choice.second.skills;
        dprint(line_prefix + "玩家 " + std::to_string(pid) + ":", false);
        for (auto skl : psp) {
            dprint(" ", false);
            print_single_skill(skl);
        }
        if (psp.size() < 1) {
            dprint(" 无");
        } else {
            // 同步换行
            dprint("");
        }
    }
    if (!print_header) return;
    int gen_sharp_cnt = 12 + 2;  // 原先井号 + 空格
    std::string gen_sharp = "";
    gen_sharp_cnt += (name == "" ? "轮次" : name).length();
    if (gen_sharp_cnt + len_offset <= 0) {
        // 加上 len_offset 后长度小于等于 0
        dprint(line_prefix + "警告: len_offset(" + std::to_string(len_offset) +
               ") 可能设置有误, 原长度为 " + std::to_string(gen_sharp_cnt));
    }
    gen_sharp_cnt += len_offset;
    for (int i = 1; i <= gen_sharp_cnt; i++) gen_sharp += "#";
    dprint(line_prefix + gen_sharp);
}

using std::cout;
using std::endl;
void RoundPatch::print() {
    cout << "##### " << id << " #####" << endl;
    if (head) cout << "本批次为第一批次" << endl;
    cout << "前驱: " << (prev_patch.empty() ? "空" : prev_patch) << endl;
    cout << "后继:";
    {
        bool flag = true;
        for (auto id : next_patch) {
            cout << " " << id;
            flag = false;
        }
        if (flag) cout << " 空";
    }
    cout << endl;
    cout << "玩家列表: ";
    {
        bool flag = true;
        for (auto player : players) {
            if (!flag) cout << ", ";
            flag = false;
            cout << player;
        }
        cout << endl;
    }
    cout << "玩家出招: " << endl;
    print_batch(choices, "", "", 0, false);
    if (!judged) {
        cout << "! 尚未计算结果" << endl;
        return;
    }
    cout << ">> 计算结果" << endl;
    cout << "玩家气数: " << endl;
    for (auto player : players) {
        cout << player << "\t";
    }
    cout << endl;
    for (auto player : players) {
        cout << formatx(qi.at(player)) << "\t";
    }
    cout << endl;
    cout << "玩家出局列表:";
    {
        bool flag = true;
        for (auto player : players) {
            if (!tag_died.at(player)) {
                continue;
            }
            cout << " " << player;
            flag = false;
        }
        if (flag) cout << " 空";
    }
    
    cout << endl;
    cout << "玩家出招计数: " << endl;
    for (auto count : skl_count) {
        auto& pid = count.first;
        auto& psp = count.second;
        cout << "\t[玩家 " << pid << "]";
        bool flag = false;
        for (auto skl : psp) {
            if (skl.second <= 0) continue;
            cout << " [" << tskl::get_skill_name((tskl::skill)skl.first) << ": " << skl.second << "]";
            flag = true;
        }
        if (!flag) cout << " 空";
        cout << endl;
    }
    cout << "玩家本批次出招: " << endl;
    for (auto player : players) {
        auto& pid = player;
        cout << "\t[玩家 " << pid << "]";
        if (skill_used.find(pid) == skill_used.end()) {
            cout << " 空" << endl;
            continue;    
        }
        auto& psp = skill_used[pid];
        bool flag = false;
        for (auto skl : psp) {
            if (skl.second == false) continue;
            cout << " " << tskl::get_skill_name(skl.first);
            flag = true;
        }
        if (!flag) cout << " 空";
        cout << endl;
    }
    cout << "本批次后需要延迟出招的玩家:";
    {
        bool flag = true;
        for (auto player : delayed_players) {
            if (player.second == false) continue;
            cout << " " << player.first;
            flag = false;
        }
        if (flag) cout << " 空";
        cout << endl;
    }
    cout << "#####";
    for (int i = 1; i <= (int)id.size() + 2; i++) cout << "#";
    cout << "#####" << endl;
}

RoundPatch RoundPatch::generate_empty(string _id, int player_cnt) {
    return generate_empty(_id, player_cnt, gen_players(player_cnt));
}

RoundPatch RoundPatch::generate_empty(string _id, int player_cnt, std::vector<int> _players) {
    return RoundPatch(
        _id,
        string(),
        _players,
        std::map<int, std::vector<Skill>>(),
        gen_qi(player_cnt),
        gen_tag_died(player_cnt),
        gen_skl_count(player_cnt),
        gen_map(player_cnt, _players, gen_repeated_vec(std::map<tskl::skill, bool>(), player_cnt)),
        gen_map(player_cnt, _players, gen_repeated_vec(false, player_cnt)),
        true,
        std::vector<string>()
    );
}

void RoundPatch::link(RoundPatch& father, RoundPatch& son) {
    father.next_patch.push_back(son.id);
    son.prev_patch = father.id;
}

void RoundPatch::link(std::map<string, RoundPatch>& data, const string father, const string son) {
    RoundPatch::link(data[father], data[son]);
}

#endif