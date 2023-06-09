#ifndef TEST_CPP
#define TEST_CPP

#include "test.h"
using tutil::TESTN;
const TESTN test1 = TESTN(
    4, gen_default_player(4),
    gen_mapx<int, int>(4, gen_default_player(4), gen_repeated_vec<int>(0, 4)),
    gen_all_alive(gen_default_player(4)),
    gen_map<int, std::map<int, int> >(4, gen_default_player(4),
                                        gen_repeated_vec(gen_cleared_skl(), 4)),
    gen_map<int, tskl::skill>(4, gen_default_player(4),
                                {tskl::clap, tskl::none, tskl::clap, tskl::none}),
    gen_map<int, int>(4, gen_default_player(4), gen_repeated_vec(0, 4)),
    gen_map<int, bool>(4, gen_default_player(4), gen_repeated_vec(false, 4)),
    gen_mapx<int, int>(4, gen_default_player(4), {1, 0, 1, 0}), "纯拍气");
const TESTN test2 = TESTN(
    4, gen_default_player(4),
    gen_mapx<int, int>(4, gen_default_player(4), gen_repeated_vec<int>(0, 4)),
    gen_all_alive(gen_default_player(4)),
    gen_map<int, std::map<int, int> >(4, gen_default_player(4),
                                      gen_repeated_vec(gen_cleared_skl(), 4)),
    gen_map<int, tskl::skill>(4, gen_default_player(4),
                              gen_repeated_vec(tskl::none, 4)),
    gen_map<int, int>(4, gen_default_player(4), gen_repeated_vec(0, 4)),
    gen_map<int, bool>(4, gen_default_player(4), gen_repeated_vec(false, 4)),
    gen_mapx<int, int>(4, gen_default_player(4), gen_repeated_vec<int>(0, 4)),
    "Null 局");

const TESTN test3 = TESTN(
    4, gen_default_player(4),
    gen_mapx<int, int>(4, gen_default_player(4), {2, 3, 6, 3}),
    gen_all_alive(gen_default_player(4)),
    gen_map<int, std::map<int, int> >(4, gen_default_player(4),
                                      gen_repeated_vec(gen_cleared_skl(), 4)),
    gen_map<int, tskl::skill>(4, gen_default_player(4),
                              {tskl::wooden_axe, tskl::normal_axe,
                               tskl::enchanted_axe, tskl::enchanted_axe}),
    gen_map<int, int>(4, gen_default_player(4), gen_repeated_vec(0, 4)),
    gen_map<int, bool>(4, gen_default_player(4), {false, false, false, true}),
    gen_mapx<int, int>(4, gen_default_player(4), {4, 5, 12, 0}), "镐局 1");

const TESTN test4 =
    TESTN(2, gen_default_player(2),
          gen_mapx<int, int>(2, gen_default_player(2), {1, 0}),
          gen_all_alive(gen_default_player(2)),
          gen_map<int, std::map<int, int> >(
              2, gen_default_player(2), gen_repeated_vec(gen_cleared_skl(), 2)),
          gen_map<int, tskl::skill>(2, gen_default_player(2),
                                    {tskl::wooden_axe, tskl::clap}),
          gen_map<int, int>(2, gen_default_player(2), gen_repeated_vec(0, 2)),
          gen_map<int, bool>(2, gen_default_player(2), {true, false}),
          gen_mapx<int, int>(2, gen_default_player(2), {0, 1}), "镐局 2");

const TESTN test5 = TESTN(
    3, gen_default_player(3),
    gen_mapx<int, int>(3, gen_default_player(3), {1, 2, 0}),
    gen_all_alive(gen_default_player(3)),
    gen_map<int, std::map<int, int> >(3, gen_default_player(3),
                                      gen_repeated_vec(gen_cleared_skl(), 3)),
    gen_map<int, tskl::skill>(3, gen_default_player(3),
                              {tskl::wooden_axe, tskl::wooden_axe, tskl::clap}),
    gen_map<int, int>(3, gen_default_player(3), gen_repeated_vec(0, 3)),
    gen_map<int, bool>(3, gen_default_player(3), {true, true, false}),
    gen_mapx<int, int>(3, gen_default_player(3), {0, 0, 1}), "镐局 3");

const TESTN test6 = TESTN(
    3, gen_default_player(3),
    gen_mapx<int, int>(3, gen_default_player(3), {1, 2, 1}),
    gen_all_alive(gen_default_player(3)),
    gen_map<int, std::map<int, int> >(3, gen_default_player(3),
                                      gen_repeated_vec(gen_cleared_skl(), 3)),
    gen_map<int, tskl::skill>(3, gen_default_player(3),
                              {tskl::wooden_axe, tskl::normal_axe, tskl::clap}),
    gen_map<int, int>(3, gen_default_player(3), gen_repeated_vec(0, 3)),
    gen_map<int, bool>(3, gen_default_player(3), {true, false, false}),
    gen_mapx<int, int>(3, gen_default_player(3), {0, 4, 2}), "镐局 4");

const TESTN test7 = TESTN(
    3, gen_default_player(3),
    gen_mapx<int, int>(3, gen_default_player(3), {0, 0, 1}),
    gen_all_alive(gen_default_player(3)),
    gen_map<int, std::map<int, int> >(3, gen_default_player(3),
                                      gen_repeated_vec(gen_cleared_skl(), 3)),
    gen_map<int, tskl::skill>(3, gen_default_player(3),
                              {tskl::clap, tskl::clap, tskl::wooden_sword}),
    gen_map<int, int>(3, gen_default_player(3), {0, 0, 1}),
    gen_map<int, bool>(3, gen_default_player(3), {true, false, false}),
    gen_mapx<int, int>(3, gen_default_player(3), {0, 1, 0}), "单剑局 1");

const TESTN test8 = TESTN(
    3, gen_default_player(3),
    gen_mapx<int, int>(3, gen_default_player(3), gen_repeated_vec<int>(0, 3)),
    gen_all_alive(gen_default_player(3)),
    gen_map<int, std::map<int, int> >(3, gen_default_player(3),
                                      gen_repeated_vec(gen_cleared_skl(), 3)),
    gen_map<int, tskl::skill>(3, gen_default_player(3),
                              {tskl::clap, tskl::clap, tskl::wooden_sword}),
    gen_map<int, int>(3, gen_default_player(3), {0, 0, 1}),
    gen_map<int, bool>(3, gen_default_player(3), {false, false, true}),
    gen_mapx<int, int>(3, gen_default_player(3), {1, 1, 0}), "单剑局 2");

const TESTN test9 =
    TESTN(2, gen_default_player(2),
          gen_mapx<int, int>(2, gen_default_player(2), {3, 1}),
          gen_all_alive(gen_default_player(2)),
          gen_map<int, std::map<int, int> >(
              2, gen_default_player(2), gen_repeated_vec(gen_cleared_skl(), 2)),
          gen_map<int, tskl::skill>(2, gen_default_player(2),
                                    {tskl::diamond_axe, tskl::wooden_sword}),
          gen_map<int, int>(2, gen_default_player(2), {0, 1}),
          gen_map<int, bool>(2, gen_default_player(2), {false, false}),
          gen_mapx<int, int>(2, gen_default_player(2), {0, 0}), "单剑局 3");

const TESTN test10 = TESTN(
    3, gen_default_player(3),
    gen_mapx<int, int>(3, gen_default_player(3), {3, 1, 1}),
    gen_map<int, bool>(3, gen_default_player(3), gen_repeated_vec(false, 3)),
    gen_map<int, std::map<int, int> >(3, gen_default_player(3),
                                      gen_repeated_vec(gen_cleared_skl(), 3)),
    gen_map<int, tskl::skill>(
        3, gen_default_player(3),
        {tskl::diamond_axe, tskl::wooden_sword, tskl::wooden_sword}),
    gen_map<int, int>(3, gen_default_player(3), {0, 1, 1}),
    gen_map<int, bool>(3, gen_default_player(3), {true, false, false}),
    gen_mapx<int, int>(3, gen_default_player(3), {0, 0, 0}), "单剑局 4");

const TESTN test11 =
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
          gen_mapx<int, int>(3, gen_default_player(3), {12, 0, 0}), "单剑局 5");

const TESTN test12 =
    TESTN(2, gen_default_player(2),
          gen_mapx<int, int>(2, gen_default_player(2), {0, 1}),
          gen_all_alive(gen_default_player(2)),
          gen_map<int, std::map<int, int> >(
              2, gen_default_player(2), gen_repeated_vec(gen_cleared_skl(), 2)),
          gen_map<int, tskl::skill>(2, gen_default_player(2),
                                    {tskl::clap, tskl::yellow_sword}),
          gen_map<int, int>(2, gen_default_player(2), {0, 1}),
          gen_map<int, bool>(2, gen_default_player(2), {true, false}),
          gen_mapx<int, int>(2, gen_default_player(2), {0, 0}), "单黄局 1");

const TESTN test13 = TESTN(
    3, gdp(3), gqx(3, gdp(3), {0, 0, 0}), gal(gdp(3)),
    gsc(3, gdp(3), grv(gcs, 3)),
    gu(3, gdp(3), {tskl::defense, tskl::hither, tskl::hither}),
    gmap(int)(3, gdp(3), {0, 0, 0}), gmap(bool)(3, gdp(3), {false, true, true}),
    gqx(3, gdp(3), {0, 0, 0}), "Hither 1");

const TESTN test14 =
    TESTN(2, gen_default_player(2),
          gen_mapx<int, int>(2, gen_default_player(2), {0, 1}),
          gen_all_alive(gen_default_player(2)),
          gen_map<int, std::map<int, int> >(
              2, gen_default_player(2), gen_repeated_vec(gen_cleared_skl(), 2)),
          gen_map<int, tskl::skill>(2, gen_default_player(2),
                                    {tskl::defense, tskl::yellow_sword}),
          gen_map<int, int>(2, gen_default_player(2), {0, 1}),
          gen_map<int, bool>(2, gen_default_player(2), {false, true}),
          gen_mapx<int, int>(2, gen_default_player(2), {0, 0}), "单黄局 2");

#endif