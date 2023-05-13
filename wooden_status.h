#ifndef WOODEN_STATUS_H
#define WOODEN_STATUS_H
#include <map>
#include <vector>
// game_status: 大局中的记录状态结构体
struct game_status {
    int player_num;
    std::vector<int>* players;
    std::map<int, float> qi;
    std::map<int, bool> tag_died;
    std::map<int, std::map<int, int> > skl_count;
    game_status();
    game_status(int);
    game_status(int&, const std::vector<int>*, const std::map<int, float>&,
                const std::map<int, bool>&,
                const std::map<int, std::map<int, int> >&);
    const int NUM_SKL = 19;
};

#endif
