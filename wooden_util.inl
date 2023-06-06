#ifndef WOODEN_UTIL_INI
#define WOODEN_UTIL_INI
#include "wooden_util.h"
using namespace tskl;

template <typename t1, typename t2>
const std::map<t1, t2> gen_map(const int player_num, const std::vector<t1> vec1,
                               const std::vector<t2> vec2) {
    assert(vec1.size() == (long long unsigned int)player_num);
    assert(vec2.size() == (long long unsigned int)player_num);
    std::map<t1, t2> mp;
    mp.clear();
    for (int i = 0; i < player_num; i++) {
        mp[vec1[i]] = vec2[i];
    }
    return mp;
}

// template const std::map<int, std::map<int, int> > gen_map(const int, const std::vector<int>, const std::vector<std::map<int, int> >);

// template const std::map<int, bool > gen_map(const int, const std::vector<int>, const std::vector<bool>);

template <typename T1, typename T2>
const std::map<T1, T2> gen_mapx(const int player_num,
                                const std::vector<T1> vec1,
                                const std::vector<T2> vec2) {
    assert(vec1.size() == (long long unsigned int)player_num);
    assert(vec2.size() == (long long unsigned int)player_num);
    std::map<T1, T2> mp;
    mp.clear();
    for (int i = 0; i < player_num; i++) {
        mp[vec1[i]] = vec2[i] * 100;
    }
    return mp;
}

// 显式实例化
template const std::map<int, int> gen_mapx(const int, const std::vector<int>, std::vector<int>);

template <typename T>
const std::vector<T> gen_repeated_vec(const T obj, const int times) {
    auto* vec = new std::vector<T>(times);
    // vector clear() 会导致 size 变为 0
    // vec->clear();
    for (int i = 0; i < times; i++) {
        (*vec)[i] = obj;
    }
    return *vec;
}

template <typename T>
bool equal_map(const std::vector<int> &_id, const std::map<int, T> &_mp1,
               const std::map<int, T> &_mp2) {
    for (auto player : _id) {
        if (_mp1.at(player) != _mp2.at(player)) return false;
    }
    return true;
}
#endif  // WOODEN_UTIL_INI