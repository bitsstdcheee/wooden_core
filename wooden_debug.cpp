#include <string>
#include <iostream>

#include "wooden_debug.h"

//dprint: debug 输出
#ifdef debug

void dprint(const std::string &msg, bool need_endl) {
    std::cout << msg;
    if (need_endl) std::cout << std::endl;
}

void dprint(const char *msg, bool need_endl) {
    std::cout << msg;
    if (need_endl) std::cout << std::endl;
}

#else
void dprint(const std::string &msg, bool need_endl) {
    return;
}

void dprint(const char *msg, bool need_endl) {
    return;
}
#endif
