#include "wooden_start.h"
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <cassert>

//通过ping检查公网连接，return 0表示ping成功
bool check_internet_connect() {
    using namespace std;
    std::vector<std::string> v;
    std::array<char, 128> buffer;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen("ping www.baidu.com -c 2 -w 2 ", "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        v.push_back(buffer.data());
    }
    //读取倒数第二行 2 packets transmitted, 2 received, 0% packet loss, time 1001ms
    if (v.size() > 1) {
        string data = v[v.size() - 2];
        int iPos = data.find("received,");
        if (iPos != -1) {
            data = data.substr(iPos - 3, 3);//截取字符串返回packet loss
            int n = atoi(data.c_str());
            if (n == 0)
                return true;
            else
                return false;
        } else {
            int iPos2 = data.find("已接收");
            if (iPos2 != -1) {
                data = data.substr(iPos + 10, 3);//截取字符串返回packet loss
                int n = atoi(data.c_str());
                if (n == 0)
                    return true;
                else
                    return false;
            }
        }
    } else {
        return true;
    }
    //cout<<"checkNet 4444: "<<endl;
}


//核心初始化
void wooden_initialization() {
    //检查公网连接
    if (check_internet_connect())//无法访问公网
    {
        internet_connect = true;
        //检测内网连接
    }
    //

    return;
}
