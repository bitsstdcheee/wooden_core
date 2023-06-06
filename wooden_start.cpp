#ifndef WOODEN_START_CPP
#define WOODEN_START_CPP
#include <array>
#include <cassert>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

#ifdef _WIN32
// clang-format off
#include <winsock2.h>
#include <netlistmgr.h>
#include <winerror.h>
#include <wininet.h>
#include <windows.h>
// clang-format on

#endif

#ifdef _linux
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#endif

#include "wooden_debug.h"
#include "wooden_start.h"

// 核心初始化
void wooden_initialization() {
#ifndef NOT_USE_CHECK_INTERNET_CONNECT
    // 检查公网连接
    if (check_internet_connect()) dprint("无法访问公网");
    { internet_connect = true; }
#endif
    // 检测内网连接
    return;
}

bool internet_connect;

// 通过ping检查公网连接，return 0表示ping成功
bool check_internet_connect() {
#ifdef _WIN32
    IUnknown *pUnknown = NULL;
    HRESULT hr = CoCreateInstance(CLSID_NetworkListManager, NULL, CLSCTX_ALL,
                                  IID_INetworkCostManager, (void **)&pUnknown);
    if (SUCCEEDED(hr)) {
        INetworkListManager *pNetworkListManager = NULL;
        hr = pUnknown->QueryInterface(IID_INetworkCostManager,
                                      (void **)&pNetworkListManager);
        if (SUCCEEDED(hr)) {
            NLM_CONNECTIVITY pConnect = NLM_CONNECTIVITY_DISCONNECTED;
            hr = pNetworkListManager->GetConnectivity(&pConnect);
            pNetworkListManager->Release();
            if (pConnect == NLM_CONNECTIVITY_IPV4_INTERNET ||
                pConnect == NLM_CONNECTIVITY_IPV6_INTERNET)
                return true;
            else
                return false;
        } else {
            return false;
        }
    } else {
        return false;
    }
#endif
#ifdef _linux
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    addr.sin_addr.s_addr = inet_addr("114.114.114.114");
    int res = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));
    close(sockfd);
    if (res == -1) return false;
    return true;
#endif
    // assert(0);
    return false;
}
#endif  // WOODEN_START_CPP