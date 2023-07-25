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

// TESTN: 玩家人数, 玩家id, 气数, 死亡标记, 招术计数器, 期望死亡标记, 期望气数,
// 备注
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
    using_skill = std::move(_using_skill);
    target = std::move(_target);
    res_tag_died = std::move(_res_tag_died);
    res_qi = std::move(_res_qi);
    comment = std::move(_comment);
    need_check = _need_check;
}

void TESTN::info() const {
    std::cout << "comment:   " << comment << std::endl;
    std::cout << "player:    " << player_num << " persons" << std::endl;
    std::cout << "id:        ";
    for (int player : players) {
        std::cout << player << "\t";
    }
    std::cout << std::endl;
    std::cout << "died:      ";
    bool flag = false;  // 标记是否输出过死亡玩家的 id
    for (int player : players) {
        if (tag_died.at(player) == false)
            std::cout << " ";
        else {
            std::cout << "*";
            flag = true;
        }
        std::cout << "\t";
    }
    if (flag == false) {
        std::cout << "\tEmpty!";
    }
    std::cout << std::endl;
    std::cout << "skl_count: " << std::endl;
    for (int player : players) {
        flag = false;
        std::cout << "\tPlayer " << player << ": ";
        if (skl_count.at(player).empty()) {
            // 理论上来说不可能出现
            assert(skl_count.at(player).empty() == false);
            std::cout << "Empty" << std::endl;
            break;
        }
        for (auto i : skl_count.at(player)) {
            if (i.second == 0) continue;
            flag = true;
            std::cout << std::endl;
            std::cout << "\t\t- " << i.first << "\t: " << i.second << " time";
            if (i.second > 1) std::cout << "s";
            std::cout << std::endl;
        }
        if (flag == false) {
            std::cout << "Empty" << std::endl;
        }
    }
    std::cout << "skill:    " << std::endl;
    for (int player : players) {
        std::cout << "\tPlayer " << player << ": ";
        if (using_skill.at(player) == tskl::none) {
            std::cout << "None";
        } else {
            std::cout << using_skill.at(player) << " -> Player "
                      << target.at(player);
        }
        std::cout << std::endl;
    }
}

void passon(const TESTN &test, bool check) {
    dprint("[P*] Entering passon()");
    const int &_player_num = test.player_num;
    assert(_player_num >= 2);  // 玩家数量需大于或等于 2

    const std::vector<int> &_players = test.players;
    const std::map<int, int> &_qi = test.qi;
    const std::map<int, bool> &_tag_died = test.tag_died;
    const std::map<int, std::map<int, int> > &_skl_count = test.skl_count;
    const std::map<int, bool> &_res_tag_died = test.res_tag_died;
    const std::map<int, int> &_res_qi = test.res_qi;
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
    auto *_dirty_choices = new std::vector<std::pair<int, Skill> >(_player_num);
    int cnt = 0;
    for (auto i : _using_skill) {
        dprint("[P0] In for: i = <" + std::to_string(i.first) + ", " +
               std::to_string(i.second) + ">, cnt = " + std::to_string(cnt));
        (*_dirty_choices)[cnt++] = std::make_pair(
            i.first,
            Skill(i.second,
                  _target.at(i.first)));  // VS 调试中发现该语句的 vector
                                          // 容器触发 assert 错误 (已修复)
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
    } else {
        dprint("[P3] I will not using assert");
        dprint(string("[P3] Check result: Died is ") +
               (equal_map(*players, _res_tag_died, tag_died)
                    ? string("Correct")
                    : string("Incorrect")) +
               string(", Qi is ") +
               (equal_map(*players, _res_qi, qi) ? string("Correct")
                                                 : string("Incorrect")));
    }

    std::cout << "Test success: " << test.comment << std::endl;
}

#endif  // WOODEN_TEST_CPP