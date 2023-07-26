#ifndef WOODEN_TEST_CPP
#define WOODEN_TEST_CPP

#include "wooden_test.h"

#define do_test(x) passon(test##x)
#define do_test_uncheck(x) passon(test##x, false)

using tutil::TESTN;

TESTN::TESTN() {
    player_num = 0;
    players.clear();
    qi.clear();
    tag_died.clear();
    skl_count.clear();
    res_tag_died.clear();
    res_qi.clear();
    need_check = false;
}

TESTN::TESTN(int _player_num, std::vector<int> _players, std::map<int, int> _qi,
             std::map<int, bool> _tag_died,
             std::map<int, std::map<int, int> > _skl_count,
             std::map<int, tskl::skill> _using_skill,
             std::map<int, int> _target, std::map<int, bool> _res_tag_died,
             std::map<int, int> _res_qi, std::string _comment,
             bool _need_check) {
    player_num = _player_num;
    players = std::move(_players);
    qi = std::move(_qi);
    tag_died = std::move(_tag_died);
    skl_count = std::move(_skl_count);
    for (auto player : _using_skill) {
        auto &pid = player.first;
        auto &skl = player.second;
        using_skill[pid] = {skl};
    }
    target = std::move(_target);
    res_tag_died = std::move(_res_tag_died);
    res_qi = std::move(_res_qi);
    comment = std::move(_comment);
    need_check = _need_check;
}

TESTN::TESTN(int _player_num, std::vector<int> _players, std::map<int, int> _qi,
             std::map<int, bool> _tag_died,
             std::map<int, std::map<int, int> > _skl_count,
             std::map<int, std::vector<tskl::skill> > _using_skill,
             std::map<int, int> _target, std::map<int, bool> _res_tag_died,
             std::map<int, int> _res_qi, std::string _comment,
             bool _need_check) {
    player_num = _player_num;
    players = std::move(_players);
    qi = std::move(_qi);
    tag_died = std::move(_tag_died);
    skl_count = std::move(_skl_count);
    for (auto player : _using_skill) {
        auto &pid = player.first;
        auto &skl = player.second;
        using_skill[pid] = skl;
    }
    target = std::move(_target);
    res_tag_died = std::move(_res_tag_died);
    res_qi = std::move(_res_qi);
    comment = std::move(_comment);
    need_check = _need_check;
}

#endif  // WOODEN_TEST_CPP