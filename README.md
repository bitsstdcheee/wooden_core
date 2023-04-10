# wooden_core

#### 介绍
木剑游戏核心判别程序

目前尚未完成，咕了

#### 如何使用
1. 在仓库根目录下新建 ```build``` 文件夹
2. 进入 ```build``` 文件夹, 执行 ```cmake .. -G "MinGW Makefiles"```
3. ```cmake``` 将在 ```build``` 文件夹下生成 ```Makefile``` 文件, 使用 ```make``` 执行即可

```cmake``` 选项:
1. 定义 ```GBK``` : ```GBK = true``` 时, 程序将以 ```GBK``` 编码输出, 否则为 ```UTF-8```

#### 贡献
当前默认分支: ```dev```
保护分支: ```master```


#### TODO
- [ ] 小局新的判断程序（```wooden_judge.cpp```Line 277，```using_new_judger```）
- [ ] 初始化
  - [ ] 网络连接检测
  - [ ] 玩家互联
  - [ ] 参数（如玩家人数等）初始化、
- [ ] 大局流程程序
- [ ] 输入输出函数
    - [ ] 与GUI交互
    - [ ] 网络连接
    - [ ] 文件读写