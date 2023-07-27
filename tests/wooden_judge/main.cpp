#include <gtest/gtest.h>

#include "test.h"

using tutil::TESTF;
using tutil::TESTK;
using tutil::TESTN;

void check(const TESTN &test, bool check) {
    dprint("[P*] Entering passon()");
    const int &_player_num = test.player_num;
    ASSERT_TRUE(_player_num >= 2);  // 玩家数量需大于或等于 2

    const std::vector<int> &_players = test.players;
    const std::map<int, int> &_qi = test.qi;
    const std::map<int, bool> &_tag_died = test.tag_died;
    const std::map<int, std::map<int, int> > &_skl_count = test.skl_count;
    const std::map<int, bool> &_res_tag_died = test.res_tag_died;
    const std::map<int, int> &_res_qi = test.res_qi;
    const std::map<int, std::vector<tskl::skill> > &_using_skill =
        test.using_skill;
    const std::map<int, int> &_target = test.target;
    const std::string &_comment = test.comment;

    // Step 0. 传入数据 -- 玩家个数断言
    dprint("[P0] Before importing data");
    ASSERT_EQ(_players.size(), (long long unsigned int)_player_num);
    ASSERT_EQ(_qi.size(), (long long unsigned int)_player_num);
    ASSERT_EQ(_tag_died.size(), (long long unsigned int)_player_num);
    ASSERT_EQ(_skl_count.size(), (long long unsigned int)_player_num);
    ASSERT_EQ(_res_tag_died.size(), (long long unsigned int)_player_num);
    ASSERT_EQ(_res_qi.size(), (long long unsigned int)_player_num);
    ASSERT_EQ(_using_skill.size(), (long long unsigned int)_player_num);
    ASSERT_EQ(_target.size(), (long long unsigned int)_player_num);

    // 转换 test::skill -> choices
    dprint("[P0] Before test::skill -> choices");
    auto *_dirty_choices = new std::vector<std::pair<int, Skill> >;
    _dirty_choices->clear();
    int cnt = 0;
    for (auto player : _using_skill) {
        auto &pid = player.first;
        for (auto skl : player.second) {
            dprint("[P0] In for: i = <" + std::to_string(pid) + ", " +
                   std::to_string(skl) + ">, cnt = " + std::to_string(++cnt));
            (*_dirty_choices)
                .push_back(std::make_pair(pid, Skill(skl, _target.at(pid))));
        }
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
        // ASSERT_TRUE(_res_tag_died == tag_died);
        // ASSERT_TRUE(_res_qi == qi);
        dprint("[P3] Before ASSERT_TRUE result");
        ASSERT_TRUE(equal_map(*players, _res_tag_died, tag_died));
        ASSERT_TRUE(equal_map(*players, _res_qi, qi));
    } else {
        dprint("[P3] I will not using ASSERT_TRUE");
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

void print_single_skill(const Skill &skl, bool need_endl = false) {
    Skill tmp = skl;
    dprint("[" + tskl::get_skill_name(tmp) + " > " +
               std::to_string(skl.target) + "]",
           need_endl);
}

// 便捷打印输入 do_main 参数.
// comment: 备注名称.
// line_prefix: 在每行开始时输出的内容, 默认值为 "[P] ".
// len_offset: 计算回收 Sharp 井号所需数量时需要加上 (负数为减去) 的长度数量,
// std::string.length() 在计算时会将全角字符处理为 1, 输出时则需要 2 个井号,
// 故需要在此参数加上. len_offset 理论上为输入字符串中全角字符的数量
void print_batch(const std::vector<std::pair<int, SkillPack> > &batch,
                 std::string comment = "", std::string line_prefix = "[P] ",
                 int len_offset = 0) {
    dprint(line_prefix + "###### " + (comment == "" ? "轮次" : comment) +
           " ######");
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
    int gen_sharp_cnt = 12 + 2;  // 原先井号 + 空格
    std::string gen_sharp = "";
    gen_sharp_cnt += (comment == "" ? "轮次" : comment).length();
    if (gen_sharp_cnt + len_offset <= 0) {
        // 加上 len_offset 后长度小于等于 0
        dprint(line_prefix + "警告: len_offset(" + std::to_string(len_offset) +
               ") 可能设置有误, 原长度为 " + std::to_string(gen_sharp_cnt));
    }
    gen_sharp_cnt += len_offset;
    for (int i = 1; i <= gen_sharp_cnt; i++) gen_sharp += "#";
    dprint(line_prefix + gen_sharp);
}

void check(const TESTF &test, bool check) {
    const int &_player_num = test.player_num;
    ASSERT_TRUE(_player_num >= 2);

    const std::vector<int> _players = test.players;
    const std::map<int, int> _qi = test.qi;
    const std::map<int, bool> _tag_died = test.tag_died;
    const std::map<int, std::map<int, int> > _skl_count = test.skl_count;
    const std::vector<TESTK> _using_skill = test.using_skill;
    const std::map<int, bool> _res_tag_died = test.res_tag_died;
    const std::map<int, int> _res_qi = test.res_qi;
    const std::string _comment = test.comment;

    ASSERT_EQ(_players.size(), (long long unsigned int)_player_num);
    ASSERT_EQ(_qi.size(), (long long unsigned int)_player_num);
    ASSERT_EQ(_tag_died.size(), (long long unsigned int)_player_num);
    ASSERT_EQ(_skl_count.size(), (long long unsigned int)_player_num);
    for (auto i : _using_skill) {
        ASSERT_EQ(i.skills.size(), (long long unsigned int)_player_num);
    }
    ASSERT_EQ(_res_tag_died.size(), (long long unsigned int)_player_num);
    ASSERT_EQ(_res_qi.size(), (long long unsigned int)_player_num);

    qi = _qi;
    tag_died = _tag_died;
    skl_count = _skl_count;
    int round_count = 0;
    for (auto round : _using_skill) {
        round_count++;
        dprint("[P] 第 " + std::to_string(round_count) + " 局, ", false);
        // 记录本局中的最大所需批次
        int batch_size = 0;
        for (auto skl : round.skills) {
            batch_size = std::max(batch_size, (int)skl.second.size());
        }
        dprint("所需批次: " + std::to_string(batch_size));
        std::map<int, bool> result;
        result.clear();
        for (int batch_index = 0; batch_index < batch_size; batch_index++) {
            dprint("[P] 第 " + std::to_string(batch_index + 1) + " 批次");
            auto *_dirty_choices = new std::vector<std::pair<int, SkillPack> >;
            // 填充当前批次的出招
            for (auto player : round.skills) {
                auto &pid = player.first;
                int batch_index_real = 0;
                if ((int)player.second.size() <= batch_index) {
                    // 当前玩家没有当前批次的出招
                    if (!result[pid]) {
                        // 上一轮提示需要该玩家再次出招
                        dprint("[P] 玩家 " + std::to_string(pid) +
                               " 在本批次中不需要更新出招, 将使用上一次");
                    } else {
                        dprint(
                            "[P] 警告: 玩家 " + std::to_string(pid) +
                            "在本批次中需要更新出招, 但未提供, 将使用先前出招");
                    }
                    batch_index_real = (int)player.second.size() - 1;
                } else {
                    // 当前玩家有当前批次的出招
                    if (!result[pid]) {
                        dprint("[P] 警告: 玩家 " + std::to_string(pid) +
                               "在本批次中不需要更新出招, 但提供了, "
                               "将本批次出招覆盖");
                    } else {
                        batch_index_real = batch_index;
                    }
                }
                dprint("[P] 玩家 " + std::to_string(pid) + " 在批次 (" +
                       std::to_string(batch_index + 1) +
                       ") 中使用的实际批次编号为 " +
                       std::to_string(batch_index_real + 1));
                SkillPack spk;
                auto &skills = player.second[batch_index_real];
                auto &target = round.target[pid];
                for (auto skl : skills) {
                    spk.skills.push_back(Skill(skl, target));
                }
                _dirty_choices->push_back(std::make_pair(pid, spk));
            }
            print_batch(*_dirty_choices,
                        "局次 " + std::to_string(round_count) + " / 批次 " +
                            std::to_string(batch_index + 1),
                        "[P] ");
            result = do_main(*_dirty_choices);
            dprint("[P] 主函数返回延迟玩家列表: ", false);
            bool has_delay = false;
            for (auto player : result) {
                if (player.second) {
                    if (has_delay) dprint(", ", false);
                    dprint(std::to_string(player.first), false);
                    has_delay = true;
                }
            }
            if (!has_delay)
                dprint("无");
            else
                dprint("", true);
        }
    }

    pretty_print_result_died((*players), tag_died);
    pretty_print_result_qi((*players), qi);

    pretty_print_result_died((*players), _res_tag_died, _comment);
    pretty_print_result_qi((*players), _res_qi, _comment);

    if (check == true) {
        ASSERT_TRUE(equal_map(*players, _res_tag_died, tag_died));
        ASSERT_TRUE(equal_map(*players, _res_qi, qi));
    }
}

class JudgeTestN : public ::testing::TestWithParam<TESTN> {};

TEST_P(JudgeTestN, small) {
    auto current_test = GetParam();
    check(current_test, current_test.need_check);
}

INSTANTIATE_TEST_SUITE_P(Testn, JudgeTestN, ::testing::ValuesIn(testn));

class JudgeTestF : public ::testing::TestWithParam<TESTF> {};

TEST_P(JudgeTestF, large) {
    auto current_test = GetParam();
    check(current_test, current_test.need_check);
}

INSTANTIATE_TEST_SUITE_P(Testf, JudgeTestF, ::testing::ValuesIn(testf));

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}