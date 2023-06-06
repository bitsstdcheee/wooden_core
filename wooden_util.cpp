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

#endif