
# 指定 CMake 版本
cmake_minimum_required(VERSION 3.15.0)

set(CMAKE_EXPORT_COMPILECOMMANDS ON)
# set(CMAKE_VERBOSE_MAKEFILE ON)

# 指定编译器
SET(CMAKE_C_COMPILER "gcc")
SET(CMAKE_CXX_COMPILER "g++")
SET(CMAKE_BUILD_TYPE "Debug")
if (GBK)
    SET(CMAKE_CXX_FLAGS_DEBUG "-Wall -g3 -ggdb -Ddebug -DDEBUG -finput-charset=UTF-8 -fexec-charset=GBK")
    SET(CMAKE_CXX_FLAGS_RELEASE "-Wall -finput-charset=UTF-8 -fexec-charset=GBK")
    message("GBK is On!")
else()
    SET(CMAKE_CXX_FLAGS_DEBUG "-Wall -g3 -ggdb -Ddebug -DDEBUG")
    SET(CMAKE_CXX_FLAGS_RELEASE "-Wall")
    message("GBK is Off!")
endif()
SET(CMAKE_CXX_FLAGS_RELEASE "-Wall")

# 指定项目名称
PROJECT(wooden_game)

# add_definitions("-Wall -g3 -ggdb -Ddebug -DDEBUG")

# 获取所有源代码文件
INCLUDE_DIRECTORIES(.)
AUX_SOURCE_DIRECTORY(. ALL_SRCS)

# .cpp 生成可执行文件
add_executable(${PROJECT_NAME} ${ALL_SRCS})

