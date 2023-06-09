#ifndef WOODEN_CORE_CPP
#define WOODEN_CORE_CPP
// 核心启动文件

#include <cassert>

#include "wooden_debug.h"
#include "wooden_judge.h"
#include "wooden_skill.h"
#include "wooden_start.h"
#include "wooden_status.h"

int main() {
    static_assert(sizeof(void *) == 8, "This program only support 64 bit.");
    assert(sizeof(void *) == 8);  // 保证运行时的 64 位环境
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

#ifdef debug

    std::cout << "This program was built on " << __DATE__ << ", " << __TIME__
              << std::endl;
    // player_num = 5;
    // players = new std::vector<int>(player_num);  // 预分配空间

    // std::cout << player_num << std::endl;

#ifdef ASSERT_TEST1
    do_test1_assert();
#endif

    // std::map<int, bool> d1 = gen_map<int, bool>(4, {1, 2, 3, 4}, {false,
    // false, false, false}); do_test(1); do_test(2); do_test(3); do_test(4);
    // do_test(5);
    // do_test(6);
    // do_test(7);
    // do_test(8);
    // do_test(9);
    // do_test(10);
    // do_test(11);
    // do_test(12);
    // do_test(13);
    // do_test(14);
    // do_test_uncheck(1);
    // do_test_uncheck(2);
    // do_test_uncheck(3);
    // do_test_uncheck(4);
    // do_test_uncheck(5);
    // do_test_uncheck(6);
    // do_test_uncheck(7);
    // do_test_uncheck(8);
    // do_test_uncheck(9);
    // do_test_uncheck(10);
    // do_test_uncheck(11);
    // do_test_uncheck(12);
    // do_test_uncheck(13);
    // do_test_uncheck(14);
#endif

    wooden_initialization();
    // 输出 Hello World

    return 0;
}

#endif  // WOODEN_CORE_CPP