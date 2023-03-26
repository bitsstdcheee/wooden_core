# wooden_core

#### 介绍
木剑游戏核心判别程序

目前尚未完成，咕了

#### 如何使用
1. 在仓库根目录下新建 ```build``` 文件夹
2. 进入 ```build``` 文件夹, 执行 ```cmake .. -G "MinGW Makefiles“```
3. ```cmake``` 将在 ```build``` 文件夹下生成 ```Makefile``` 文件, 使用 ```make``` 执行即可

```cmake``` 选项:
1. 定义 ```GBK``` : ```GBK = true``` 时, 程序将以 ```GBK``` 编码输出, 否则为 ```UTF-8```
