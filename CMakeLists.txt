
# 指定 CMake 版本
cmake_minimum_required(VERSION 3.15.0)

# 指定项目名称
PROJECT(wooden_game)

set(CMAKE_EXPORT_COMPILECOMMANDS ON)
# set(CMAKE_VERBOSE_MAKEFILE ON)

# 指定编译器
SET(CMAKE_C_COMPILER "gcc")
SET(CMAKE_CXX_COMPILER "g++")
SET(CMAKE_CXX_FLAGS_GBK "-finput-charset=UTF-8 -fexec-charset=GBK")
if (GBK)
    SET(CMAKE_CXX_FLAGS_DEBUG STRING(CONCAT "-Wall -g3 -ggdb -o0 -Ddebug -DDEBUG " ${CMAKE_CXX_FLAGS_GBK}))
    SET(CMAKE_CXX_FLAGS_RELEASE "-Wall " ${CMAKE_CXX_FLAGS_GBK})
    message("GBK is On!")
else()
    SET(CMAKE_CXX_FLAGS_DEBUG "-Wall -g3 -ggdb -Ddebug -DDEBUG")
    SET(CMAKE_CXX_FLAGS_RELEASE "-Wall")
    message("GBK is Off!")
endif()


# add_definitions("-Wall -g3 -ggdb -Ddebug -DDEBUG")

# 获取所有源代码文件
# file (GLOB HEADERS
    # .)
# INCLUDE_DIRECTORIES(.)
# AUX_SOURCE_DIRECTORY(. ALL_SRCS)

file (GLOB SOURCES
    *.cpp
)

# .cpp 生成可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})

