#ifndef WOODEN_GAME_WOODEN_START_H
#define WOODEN_GAME_WOODEN_START_H

// #define NOT_USE_CHECK_INTERNET_CONNECT

void wooden_initialization();

#ifndef NOT_USE_CHECK_INTERNET_CONNECT
extern bool internet_connect;
bool check_internet_connect();
#endif

#endif  // WOODEN_GAME_WOODEN_START_H
