#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <iostream>
#include <cassert>
#include <array>

#include "wooden_start.h"
#include "wooden_debug.h"
bool internet_connect;
//通过ping检查公网连接，return 0表示ping成功
bool check_internet_connect() {
    using namespace std;
    try {
        std::vector<std::string> v;
        std::array<char, 128> buffer;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen("ping www.baidu.com -c 2 -w 2 ", "r"), pclose);
        if (!pipe) {
            throw std::runtime_error("popen() failed!");
        }
        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
            dprint(buffer.data());
            v.push_back(buffer.data());
        }
        //读取倒数第二行 2 packets transmitted, 2 received, 0% packet loss, time 1001ms
        if (v.size() > 1) {
            string data = v[v.size() - 2];
            dprint(data);
            int iPos = data.find("received,");
            if (iPos != -1) {
                data = data.substr(iPos - 3, 3);//截取字符串返回packet loss
                dprint(data);
                int n = atoi(data.c_str());
                dprint(to_string(n));
                if (n == 0)
                    return true;
                else
                    return false;
            } else {
                int iPos2 = data.find("已接收");
                if (iPos2 != -1) {
                    data = data.substr(iPos + 10, 3);//截取字符串返回packet loss
                    dprint(data);
                    int n = atoi(data.c_str());
                    dprint(to_string(n));
                    if (n == 0)
                        return true;
                    else
                        return false;
                }
            }
        } else {
            return true;
        }
    } catch (std::exception	e) {
        string error_info = e.what();
        dprint(error_info);
        assert(1);
        //ogWriteSql("1.checkNet() 判断是否有网络 error");
    }
    //cout<<"checkNet 4444: "<<endl;
    return false;
}


//核心初始化
void wooden_initialization() {
    //检查公网连接
    if (check_internet_connect())dprint("无法访问公网");
    {
        internet_connect = true;
        //检测内网连接
    }
    return ;
}
