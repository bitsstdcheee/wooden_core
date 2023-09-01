#ifndef TEST_CPP
#define TEST_CPP

#include "test.h"

#include "wooden_skill.h"
#include "wooden_util.h"
using tutil::TESTF;
using tutil::TESTK;
using tutil::TESTKG;
using tutil::TESTN;

const std::list<TESTN> testn = {
    TESTN(4, gen_default_player(4),
          gen_mapx<int, int>(4, gen_default_player(4),
                             gen_repeated_vec<int>(0, 4)),
          gen_all_alive(gen_default_player(4)),
          gen_map<int, std::map<int, int> >(
              4, gen_default_player(4), gen_repeated_vec(gen_cleared_skl(), 4)),
          gen_map<int, tskl::skill>(
              4, gen_default_player(4),
              {tskl::clap, tskl::none, tskl::clap, tskl::none}),
          gen_map<int, int>(4, gen_default_player(4), gen_repeated_vec(0, 4)),
          gen_map<int, bool>(4, gen_default_player(4),
                             gen_repeated_vec(false, 4)),
          gen_mapx<int, int>(4, gen_default_player(4), {1, 0, 1, 0}), "纯拍气"),
    TESTN(4, gen_default_player(4),
          gen_mapx<int, int>(4, gen_default_player(4),
                             gen_repeated_vec<int>(0, 4)),
          gen_all_alive(gen_default_player(4)),
          gen_map<int, std::map<int, int> >(
              4, gen_default_player(4), gen_repeated_vec(gen_cleared_skl(), 4)),
          gen_map<int, tskl::skill>(4, gen_default_player(4),
                                    gen_repeated_vec(tskl::none, 4)),
          gen_map<int, int>(4, gen_default_player(4), gen_repeated_vec(0, 4)),
          gen_map<int, bool>(4, gen_default_player(4),
                             gen_repeated_vec(false, 4)),
          gen_mapx<int, int>(4, gen_default_player(4),
                             gen_repeated_vec<int>(0, 4)),
          "Null 局"),

    TESTN(4, gen_default_player(4),
          gen_mapx<int, int>(4, gen_default_player(4), {2, 3, 6, 3}),
          gen_all_alive(gen_default_player(4)),
          gen_map<int, std::map<int, int> >(
              4, gen_default_player(4), gen_repeated_vec(gen_cleared_skl(), 4)),
          gen_map<int, tskl::skill>(4, gen_default_player(4),
                                    {tskl::wooden_axe, tskl::normal_axe,
                                     tskl::enchanted_axe, tskl::enchanted_axe}),
          gen_map<int, int>(4, gen_default_player(4), gen_repeated_vec(0, 4)),
          gen_map<int, bool>(4, gen_default_player(4),
                             {false, false, false, true}),
          gen_mapx<int, int>(4, gen_default_player(4), {4, 5, 12, 0}),
          "镐局 1"),

    TESTN(2, gen_default_player(2),
          gen_mapx<int, int>(2, gen_default_player(2), {1, 0}),
          gen_all_alive(gen_default_player(2)),
          gen_map<int, std::map<int, int> >(
              2, gen_default_player(2), gen_repeated_vec(gen_cleared_skl(), 2)),
          gen_map<int, tskl::skill>(2, gen_default_player(2),
                                    {tskl::wooden_axe, tskl::clap}),
          gen_map<int, int>(2, gen_default_player(2), gen_repeated_vec(0, 2)),
          gen_map<int, bool>(2, gen_default_player(2), {true, false}),
          gen_mapx<int, int>(2, gen_default_player(2), {0, 1}), "镐局 2"),

    TESTN(3, gen_default_player(3),
          gen_mapx<int, int>(3, gen_default_player(3), {1, 2, 0}),
          gen_all_alive(gen_default_player(3)),
          gen_map<int, std::map<int, int> >(
              3, gen_default_player(3), gen_repeated_vec(gen_cleared_skl(), 3)),
          gen_map<int, tskl::skill>(
              3, gen_default_player(3),
              {tskl::wooden_axe, tskl::wooden_axe, tskl::clap}),
          gen_map<int, int>(3, gen_default_player(3), gen_repeated_vec(0, 3)),
          gen_map<int, bool>(3, gen_default_player(3), {true, true, false}),
          gen_mapx<int, int>(3, gen_default_player(3), {0, 0, 1}), "镐局 3"),

    TESTN(3, gen_default_player(3),
          gen_mapx<int, int>(3, gen_default_player(3), {1, 2, 1}),
          gen_all_alive(gen_default_player(3)),
          gen_map<int, std::map<int, int> >(
              3, gen_default_player(3), gen_repeated_vec(gen_cleared_skl(), 3)),
          gen_map<int, tskl::skill>(
              3, gen_default_player(3),
              {tskl::wooden_axe, tskl::normal_axe, tskl::clap}),
          gen_map<int, int>(3, gen_default_player(3), gen_repeated_vec(0, 3)),
          gen_map<int, bool>(3, gen_default_player(3), {true, false, false}),
          gen_mapx<int, int>(3, gen_default_player(3), {0, 4, 2}), "镐局 4"),

    TESTN(
        3, gen_default_player(3),
        gen_mapx<int, int>(3, gen_default_player(3), {0, 0, 1}),
        gen_all_alive(gen_default_player(3)),
        gen_map<int, std::map<int, int> >(
            3, gen_default_player(3), gen_repeated_vec(gen_cleared_skl(), 3)),
        gen_map<int, tskl::skill>(3, gen_default_player(3),
                                  {tskl::clap, tskl::clap, tskl::wooden_sword}),
        gen_map<int, int>(3, gen_default_player(3), {0, 0, 1}),
        gen_map<int, bool>(3, gen_default_player(3), {true, false, false}),
        gen_mapx<int, int>(3, gen_default_player(3), {0, 1, 0}), "单剑局 1"),

    TESTN(
        3, gen_default_player(3),
        gen_mapx<int, int>(3, gen_default_player(3),
                           gen_repeated_vec<int>(0, 3)),
        gen_all_alive(gen_default_player(3)),
        gen_map<int, std::map<int, int> >(
            3, gen_default_player(3), gen_repeated_vec(gen_cleared_skl(), 3)),
        gen_map<int, tskl::skill>(3, gen_default_player(3),
                                  {tskl::clap, tskl::clap, tskl::wooden_sword}),
        gen_map<int, int>(3, gen_default_player(3), {0, 0, 1}),
        gen_map<int, bool>(3, gen_default_player(3), {false, false, true}),
        gen_mapx<int, int>(3, gen_default_player(3), {1, 1, 0}), "单剑局 2"),

    TESTN(2, gen_default_player(2),
          gen_mapx<int, int>(2, gen_default_player(2), {3, 1}),
          gen_all_alive(gen_default_player(2)),
          gen_map<int, std::map<int, int> >(
              2, gen_default_player(2), gen_repeated_vec(gen_cleared_skl(), 2)),
          gen_map<int, tskl::skill>(2, gen_default_player(2),
                                    {tskl::diamond_axe, tskl::wooden_sword}),
          gen_map<int, int>(2, gen_default_player(2), {0, 1}),
          gen_map<int, bool>(2, gen_default_player(2), {false, false}),
          gen_mapx<int, int>(2, gen_default_player(2), {0, 0}), "单剑局 3"),

    TESTN(3, gen_default_player(3),
          gen_mapx<int, int>(3, gen_default_player(3), {3, 1, 1}),
          gen_map<int, bool>(3, gen_default_player(3),
                             gen_repeated_vec(false, 3)),
          gen_map<int, std::map<int, int> >(
              3, gen_default_player(3), gen_repeated_vec(gen_cleared_skl(), 3)),
          gen_map<int, tskl::skill>(
              3, gen_default_player(3),
              {tskl::diamond_axe, tskl::wooden_sword, tskl::wooden_sword}),
          gen_map<int, int>(3, gen_default_player(3), {0, 1, 1}),
          gen_map<int, bool>(3, gen_default_player(3), {true, false, false}),
          gen_mapx<int, int>(3, gen_default_player(3), {0, 0, 0}), "单剑局 4"),

    TESTN(3, gen_default_player(3),
          gen_mapx<int, int>(3, gen_default_player(3), {6, 1, 1}),
          gen_all_alive(gen_default_player(3)),
          gen_map<int, std::map<int, int> >(
              3, gen_default_player(3), gen_repeated_vec(gen_cleared_skl(), 3)),
          gen_map<int, tskl::skill>(
              3, gen_default_player(3),
              {tskl::enchanted_axe, tskl::wooden_sword, tskl::wooden_sword}),
          gen_map<int, int>(3, gen_default_player(3), {0, 1, 1}),
          gen_map<int, bool>(3, gen_default_player(3), {false, false, false}),
          gen_mapx<int, int>(3, gen_default_player(3), {12, 0, 0}), "单剑局 5"),

    TESTN(2, gen_default_player(2),
          gen_mapx<int, int>(2, gen_default_player(2), {0, 1}),
          gen_all_alive(gen_default_player(2)),
          gen_map<int, std::map<int, int> >(
              2, gen_default_player(2), gen_repeated_vec(gen_cleared_skl(), 2)),
          gen_map<int, tskl::skill>(2, gen_default_player(2),
                                    {tskl::clap, tskl::yellow_sword}),
          gen_map<int, int>(2, gen_default_player(2), {0, 1}),
          gen_map<int, bool>(2, gen_default_player(2), {true, false}),
          gen_mapx<int, int>(2, gen_default_player(2), {0, 0}), "单黄局 1"),

    TESTN(3, gdp(3), gqx(3, gdp(3), {0, 0, 0}), gal(gdp(3)),
          gsc(3, gdp(3), grv(gcs, 3)),
          gu(3, gdp(3), {tskl::defense, tskl::hither, tskl::hither}),
          gmap(int)(3, gdp(3), {0, 0, 0}),
          gmap(bool)(3, gdp(3), {false, true, true}), gqx(3, gdp(3), {0, 0, 0}),
          "Hither 1"),

    TESTN(2, gen_default_player(2),
          gen_mapx<int, int>(2, gen_default_player(2), {0, 1}),
          gen_all_alive(gen_default_player(2)),
          gen_map<int, std::map<int, int> >(
              2, gen_default_player(2), gen_repeated_vec(gen_cleared_skl(), 2)),
          gen_map<int, tskl::skill>(2, gen_default_player(2),
                                    {tskl::defense, tskl::yellow_sword}),
          gen_map<int, int>(2, gen_default_player(2), {0, 1}),
          gen_map<int, bool>(2, gen_default_player(2), {false, true}),
          gen_mapx<int, int>(2, gen_default_player(2), {0, 0}), "单黄局 2"),

    TESTN(3, gen_default_player(3),
          gen_mapx<int, int>(3, gen_default_player(3), {2, 0, 0}),
          gen_all_alive(gen_default_player(3)),
          gen_map<int, std::map<int, int> >(
              3, gen_default_player(3), gen_repeated_vec(gen_cleared_skl(), 3)),
          gen_map<int, tskl::skill>(3, gen_default_player(3),
                                    {tskl::alpaca, tskl::clap, tskl::clap}),
          gen_map<int, int>(3, gen_default_player(3), {0, 0, 0}),
          gen_map<int, bool>(3, gen_default_player(3), {false, true, true}),
          gen_map<int, int>(3, gen_default_player(3), {0, 0, 0}), "Alpaca 1"),

    TESTN(3, gen_default_player(3),
          gen_mapx<int, int>(3, gen_default_player(3), {2, 1, 0}),
          gen_all_alive(gen_default_player(3)),
          gen_map<int, std::map<int, int> >(
              3, gen_default_player(3), gen_repeated_vec(gen_cleared_skl(), 3)),
          gen_map<int, tskl::skill>(3, gen_default_player(3),
                                    {tskl::alpaca, tskl::hither, tskl::judge}),
          gen_map<int, int>(3, gen_default_player(3), {0, 0, 0}),
          gen_map<int, bool>(3, gen_default_player(3), {true, false, true}),
          gen_map<int, int>(3, gen_default_player(3), {0, 0, 0}), "Alpaca 2.1",
          true),

    TESTN(
        3, gen_default_player(3),
        gen_mapx<int, int>(3, gen_default_player(3), {2, 1, 0}),
        gen_all_alive(gen_default_player(3)),
        gen_map<int, std::map<int, int> >(
            3, gen_default_player(3), gen_repeated_vec(gen_cleared_skl(), 3)),
        gen_map<int, tskl::skill>(3, gen_default_player(3),
                                  {tskl::alpaca, tskl::hither, tskl::defense}),
        gen_map<int, int>(3, gen_default_player(3), {0, 0, 0}),
        gen_map<int, bool>(3, gen_default_player(3), {true, false, false}),
        gen_map<int, int>(3, gen_default_player(3), {0, 0, 0}), "Alpaca 2.2",
        true),

    TESTN(2, gen_players(2), gen_qi({1, 1}), gen_tag_died(2), gen_skl_count(2),
          gen_using_skill({tskl::wooden_axe, tskl::wooden_sword}),
          gen_target({0, 1}), gen_res_tag_died({true, false}),
          gen_res_qi({0, 0}), "木剑-木镐局"),

    TESTN(2, gen_players(2), gen_qi({1, 0}), gen_tag_died(2), gen_skl_count(2),
          gen_using_skill({tskl::mid_defense, tskl::clap}), gen_target({0, 0}),
          gen_tag_died({true, false}), gen_res_qi({0, 1}), "中防-破防局"),

    TESTN(4, gen_players(4), gen_qi({1, 0, 1, 0}), gen_tag_died(4),
          gen_skl_count(4),
          gen_using_skill({tskl::yellow_sword, tskl::yellow_sword,
                           tskl::yellow_sword, tskl::defense}),
          gen_target({2, 3, 4, 0}),
          gen_res_tag_died({false, true, true, false}),
          gen_res_qi({0, 0, 0, 0}), "黄剑-连锁局"),

    TESTN(4, gen_players(4), gen_qi({0, 1, 0, 1}), gen_tag_died(4),
          gen_skl_count(4),
          gen_using_skill({tskl::defense, tskl::yellow_sword,
                           tskl::yellow_sword, tskl::yellow_sword}),
          gen_target({0, 1, 2, 3}),
          gen_res_tag_died({false, true, true, false}), gen_qi({0, 0, 0, 0}),
          "黄剑-连锁局(反转)"),

    TESTN(2, gen_players(2), gen_qi({3, 1}), gen_tag_died(2), gen_skl_count(2),
          gen_using_skill(
              {{1, {tskl::mid_defense, tskl::mid_defense, tskl::mid_defense}},
               {2, {tskl::yellow_sword}}}),
          gen_target({0, 1}), gen_res_tag_died({true, false}),
          gen_res_qi({0, 0}), "中防-黄剑-破防局1", false),

    TESTN(2, gen_players(2), gen_qi({3, 0}), gen_tag_died(2), gen_skl_count(2),
          gen_using_skill(
              {{1, {tskl::mid_defense, tskl::mid_defense, tskl::mid_defense}},
               {2, {tskl::yellow_sword}}}),
          gen_target({0, 1}), gen_res_tag_died({true, true}),
          gen_res_qi({0, 0}), "中防-黄剑-破防局2", false),
    // test 中防-黄剑-破防局 的测试数据上不符合 中防不可叠加 的规则

    TESTN(
        2, gen_players(2), gen_qi({10, 1}), gen_tag_died(2), gen_skl_count(2),
        gen_using_skill({{1,
                          {tskl::normal_axe, tskl::normal_axe, tskl::normal_axe,
                           tskl::normal_axe, tskl::normal_axe}},
                         {2, {tskl::yellow_sword}}}),
        gen_target({0, 1}), gen_res_tag_died({false, true}), gen_res_qi({0, 0}),
        "钻镐-黄剑-破镐局"),

    TESTN(2, gen_players(2), gen_qi({12, 1}), gen_tag_died(2), gen_skl_count(2),
          gen_using_skill(
              {{1,
                {tskl::normal_axe, tskl::normal_axe, tskl::normal_axe,
                 tskl::normal_axe, tskl::normal_axe, tskl::normal_axe}},
               {2, {tskl::yellow_sword}}}),
          gen_target({0, 1}), gen_res_tag_died({false, true}),
          gen_res_qi({24, 0}), "钻镐-黄剑"),

    TESTN(2, gen_players(2), gen_qi({0, 1}), gen_tag_died(2), gen_skl_count(2),
          gen_using_skill({tskl::fetch_sword, tskl::wooden_sword}),
          gen_target({2, 1}), gen_res_tag_died({false, false}),
          gen_res_qi({int(1.5 * 100), 0}, false), "夹剑-木剑"),

    TESTN(2, gen_players(2), gen_qi({1, 0}), gen_tag_died(2), gen_skl_count(2),
          gen_using_skill({tskl::wooden_sword, tskl::fetch_sword}),
          gen_target({2, 1}), gen_res_tag_died({false, false}),
          gen_res_qi({0, int(1.5 * 100)}, false), "夹剑-木剑(反转顺序)"),

    TESTN(2, gen_players(2), gen_qi({0, 1}), gen_tag_died(2), gen_skl_count(2),
          gen_using_skill({tskl::fetch_sword, tskl::yellow_sword}),
          gen_target({2, 1}), gen_tag_died({false, true}), gen_res_qi({3, 0}),
          "夹剑-黄剑"),

    TESTN(2, gen_players(2), gen_qi({0, 1}), gen_tag_died(2), gen_skl_count(2),
          gen_using_skill(
              {{1, {tskl::fetch_fist}}, {2, {tskl::fist, tskl::fist}}}),
          gen_target({2, 1}), gen_res_tag_died({false, false}),
          gen_res_qi({int(0.5 * 100), 0}, false), "夹拳-正常"),

    TESTN(2, gen_players(2), gen_qi({0, 1}), gen_tag_died(2), gen_skl_count(2),
          gen_using_skill({tskl::fetch_fist, tskl::wooden_sword}),
          gen_target({2, 1}), gen_res_tag_died({true, false}),
          gen_res_qi({0, 0}), "夹拳-木剑"),

    TESTN(2, gen_players(2), gen_qi({0, 1}), gen_tag_died(2), gen_skl_count(2),
          gen_using_skill({tskl::fetch_bo, tskl::bo_sword}), gen_target({2, 1}),
          gen_res_tag_died({false, false}),
          gen_res_qi({int(3.5 * 100), 0}, false), "夹波波剑-正常"),

    TESTN(2, gen_players(2), gen_qi({2, 0}), gen_tag_died(2), gen_skl_count(2),
          gen_using_skill({tskl::gulu, tskl::judge}), gen_target({0, 1}),
          gen_res_tag_died({true, false}), gen_res_qi({0, 0}),
          "咕噜咕噜-评测")};

const int TESTN_NUM = testn.size();

const std::list<TESTF> testf = {
    TESTF(2, gen_players(2), gen_qi({0, 0}), gen_tag_died(2), gen_skl_count(2),
          {
              TESTK({{1, {{tskl::clap}}}, {2, {{tskl::clap}}}},
                    gen_target({2, 1}), {{1, 1}, {2, 1}}),
              TESTK({{1, {{tskl::clap}}}, {2, {{tskl::wooden_sword}}}},
                    gen_target({2, 1}), {{1, 1}, {2, 1}}),
          },
          gen_res_tag_died({true, false}), gen_res_qi({0, 0}), "大局-测试1"),

    TESTF(2, gen_players(2), gen_qi({0, 0}), gen_tag_died(2), gen_skl_count(2),
          {
              TESTK({{1, {{tskl::clap}}}, {2, {{tskl::clap}}}},
                    gen_target({0, 0}), {{1, 1}, {2, 1}}),
              TESTK({{1, {{tskl::clap}}}, {2, {{tskl::clap}}}},
                    gen_target({0, 0}), {{1, 1}, {2, 1}}),
              TESTK({{1, {{tskl::clap}}}, {2, {{tskl::clap}}}},
                    gen_target({0, 0}), {{1, 1}, {2, 1}}),
              TESTK({{1, {{tskl::clap}}},
                     {2, {{tskl::gulu}, {tskl::wooden_sword}}}},
                    gen_target({0, 1}), {{1, 1}, {2, 2}}),
          },
          gen_res_tag_died({true, false}), gen_res_qi({0, 0}),
          "大局-测试延迟1"),

    TESTF(3, gen_players(3), gen_qi({0, 0, 0}), gen_tag_died(3),
          gen_skl_count(3),
          {TESTK({{1, {{Skill(tskl::clap, 0)}}},
                  {2, {{Skill(tskl::clap, 0)}}},
                  {3, {{Skill(tskl::clap, 0)}}}},
                 {{1, 1}, {2, 1}, {3, 1}}),
           TESTK({{1, {{Skill(tskl::defense, 0)}}},
                  {2, {{Skill(tskl::wooden_sword, 1)}}},
                  {3, {{Skill(tskl::wooden_sword, 1)}}}},
                 {{1, 1}, {2, 1}, {3, 1}}),
           TESTK({{1, {{Skill(tskl::fist, 2), Skill(tskl::fist, 3)}}},
                  {2, {{Skill(tskl::clap, 0)}}},
                  {3, {{Skill(tskl::clap, 0)}}}},
                 {{1, 1}, {2, 1}, {3, 1}})},
          gen_tag_died({false, true, true}), gen_res_qi({0, 0, 0}),
          "大局-测试多对象1"),

    TESTF(3, gen_players(3), gen_qi({0, 0, 0}), gen_tag_died(3),
          gen_skl_count(3),
          {TESTKG({{1, {Skill(tskl::clap, 0)}},
                   {2, {Skill(tskl::clap, 0)}},
                   {3, {Skill(tskl::clap, 0)}}}),
           TESTKG({{1, {Skill(tskl::defense, 0)}},
                   {2, {Skill(tskl::wooden_sword, 1)}},
                   {3, {Skill(tskl::wooden_sword, 1)}}}),
           TESTK({{1, {{Skill(tskl::fist, 2), Skill(tskl::fist, 3)}}},
                  {2, {{Skill(tskl::clap, 0)}}},
                  {3, {{Skill(tskl::clap, 0)}}}},
                 {{1, 1}, {2, 1}, {3, 1}})},
          gen_tag_died({false, true, true}), gen_res_qi({0, 0, 0}),
          "大局-测试多对象1-remake"),

    TESTF(3, gen_players(3), gen_qi({0, 0, 0}), gen_tag_died(3),
          gen_skl_count(3),
          {
              TESTKG({{1, {Skill(tskl::clap, 0)}},
                      {2, {Skill(tskl::clap, 0)}},
                      {3, {Skill(tskl::clap, 0)}}}),
              TESTKG({{1, {Skill(tskl::clap, 0)}},
                      {2, {Skill(tskl::clap, 0)}},
                      {3, {Skill(tskl::clap, 0)}}}),
              TESTKG({// 此处玩家 1 应该被玩家 2 的 Judge 判定出局, 故出的 Clap
                      // 实际上无效
                      {1, {Skill(tskl::gulu, 0), Skill(tskl::clap, 0)}},
                      {2, {Skill(tskl::judge, 0)}},
                      {3, {Skill(tskl::stone_sword, 2)}}}),
          },
          gen_tag_died({true, true, false}), gen_res_qi({0, 0, 0}),
          "大局-咕噜评测局1", true,
          "本局测试评测顺序是否正确, 可以看出即使 P2 被 P3 的石剑出局, 但 P2 "
          "的评测效果仍然有效, 使 P1 出局, 且 P1 第2批次的拍手技能无效"),
      
      TESTF(3, gen_players(3), gen_qi({0, 0, 0}), gen_tag_died(3), gen_skl_count(3),
      {
            TESTKG({{1, {Skill(tskl::clap, 0)}},
            {2, {Skill(tskl::clap, 0)}},
            {3, {Skill{tskl::clap, 0}}}}),
            TESTKG({{1, {Skill(tskl::clap, 0)}},
            {2, {Skill(tskl::clap, 0)}},
            {3, {Skill{tskl::clap, 0}}}}),
            TESTKG({{1, {Skill(tskl::clap, 0)}},
            {2, {Skill(tskl::clap, 0)}},
            {3, {Skill{tskl::clap, 0}}}}),
            TESTK({{1, {{Skill(tskl::tube, 0), Skill(tskl::tube, 0)}, {Skill(tskl::tube_selected, 2), Skill(tskl::tube_selected, 3)}}},
            {2, {{Skill(tskl::clap, 0)}}},
            {3, {{Skill(tskl::defense, 0)}}}},
            {{1, 2}, {2, 1}, {3, 1}})
      }, gen_tag_died({false, true, false}), gen_res_qi({0, 0, 3}),
      "大局-管局1", true, "本局测试基本的管类招式是否正常")

};

const int TESTF_NUM = testf.size();

#endif