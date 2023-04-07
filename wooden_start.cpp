#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <cassert>
#include <array>

#include "wooden_start.h"
#include "wooden_debug.h"

// 核心初始化
void wooden_initialization() {
#ifndef NOT_USE_CHECK_INTERNET_CONNECT
    // 检查公网连接
    if (check_internet_connect()) dprint("无法访问公网");
    {
        internet_connect = true;
        // 检测内网连接
    }
#endif
    return ;
}

#ifndef NOT_USE_CHECK_INTERNET_CONNECT
bool internet_connect;
// 通过ping检查公网连接，return 0表示ping成功
bool check_internet_connect() {
    throw -1;
    return false;
}
#endif
