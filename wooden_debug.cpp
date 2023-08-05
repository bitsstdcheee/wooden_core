#ifndef WOODEN_DEBUG_CPP
#define WOODEN_DEBUG_CPP
#include "wooden_debug.h"

#include <iostream>

// dprint: debug 输出
#ifdef DEBUG

void dprint(const std::string &msg, bool need_endl) {
    std::cout << msg;
    if (need_endl) std::cout << std::endl;
}

void dprint(const char *msg, bool need_endl) {
    std::cout << msg;
    if (need_endl) std::cout << std::endl;
}

#else
void dprint(const std::string &msg, bool need_endl) { return; }

void dprint(const char *msg, bool need_endl) { return; }
#endif

#endif  // WOODEN_DEBUG_CPP