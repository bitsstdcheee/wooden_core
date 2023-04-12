#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <cassert>
#include <array>

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#endif

#ifdef _linux
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#endif

#include "wooden_start.h"
#include "wooden_debug.h"

// 核心初始化
void wooden_initialization() {
#ifndef NOT_USE_CHECK_INTERNET_CONNECT
    // 检查公网连接
    if (check_internet_connect()) dprint("无法访问公网");
    {
        internet_connect = true;

    }
#endif
    // 检测内网连接
    return;
}

bool internet_connect;

// 通过ping检查公网连接，return 0表示ping成功
bool check_internet_connect() {
    
    #ifdef _WIN32
    DWORD flag;
    BOOL con = InternetGetConnectedState(&flag, 0);
    return con == TRUE;
    #endif
    #ifdef _linux
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    addr.sin_addr.s_addr = inet_addr("114.114.114.114");
    int res = connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    close(sockfd);
    if (res == -1) return false;
    return true;
    #endif
    assert(0);
}
