#ifndef WOODEN_UTIL_CPP
#define WOODEN_UTIL_CPP

#include "wooden_util.h"
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

const std::map<int, int> gen_res_qi(std::initializer_list<int> qi, bool enable_x) {
    return gen_qi(qi, enable_x);
}

#endif