
# 指定 CMake 版本
cmake_minimum_required(VERSION 3.15.0)

# 指定项目名称
PROJECT(wooden_game)

set(CMAKE_EXPORT_COMPILECOMMANDS ON)
set(CMAKE_VERBOSE_MAKEFILE ON)
set(ENABLE_COVERAGE ON)

if (APPLE)
# MacOS 系统不支持静态编译, 因为该平台上提供的库文件并没有进行静态编译
# Error Message: (in https://github.com/bitsstdcheee/wooden_core/actions/runs/4820579102/jobs/8585266114)
# ld: library not found for -lcrt0.o
# Stack Overflow: https://stackoverflow.com/questions/3801011/ld-library-not-found-for-lcrt0-o-on-osx-10-6-with-gcc-clang-static-flag pu
else ()
# 设置静态编译
    set(CMAKE_EXE_LINKER_FLAGS "-static")
endif ()

# 输出 Worker 信息
message("The basic infomation:")
message("PROJECT_SOURCE_DIR ${PROJECT_SOURCE_DIR}")
message("PROJECT_BINARY_DIR ${PROJECT_BINARY_DIR}")
message("PROJECT_NAME ${PROJECT_NAME}")
message("CMAKE_CURRENT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}")
message("CMAKE_CURRENT_BINARY_DIR ${CMAKE_CURRENT_BINARY_DIR}")
message("CMAKE_CURRENT_LIST_DIR ${CMAKE_CURRENT_LIST_DIR}")
message("EXECUTABLE_OUTPUT_PATH ${EXECUTABLE_OUTPUT_PATH}")
message("======= System =======")
message("CMAKE_MAJOR_VERSION ${CMAKE_MAJOR_VERSION}")
message("CMAKE_MINOR_VERSION ${CMAKE_MINOR_VERSION}")
message("CMAKE_PATCH_VERSION ${CMAKE_PATCH_VERSION}")
message("CMAKE_SYSTEM ${CMAKE_SYSTEM}")
message("CMAKE_SYSTEM_NAME ${CMAKE_SYSTEM_PROCESSOR}")
message("CMAKE_SYSTEM_VERSION ${CMAKE_SYSTEM_VERSION}")
message("CMAKE_SYSTEM_PROCESSOR ${CMAKE_SYSTEM_PROCESSOR}")
message("UNIX ${UNIX}")
message("WIN32 ${WIN32}")

# 指定编译器
SET(CMAKE_C_COMPILER "gcc")
SET(CMAKE_CXX_COMPILER "g++")
SET(CMAKE_CXX_FLAGS_GBK "-finput-charset=UTF-8 -fexec-charset=GBK")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage -std=c++17")
if (GBK)
    SET(CMAKE_CXX_FLAGS_DEBUG "-Wall -g3 -ggdb -O0 -Ddebug -DDEBUG ${CMAKE_CXX_FLAGS_GBK}")
    SET(CMAKE_CXX_FLAGS_RELEASE "-Wall ${CMAKE_CXX_FLAGS_GBK}")
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
file (GLOB HEADERS
    *.h
)

# .cpp 生成可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})

if (WIN32) 
    target_link_libraries(${PROJECT_NAME} 
        Wininet.lib
        ole32.lib
        )
    if (FALSE)
        link_directories(
            Wininet.lib
            ole32.lib
            )
    endif ()
elseif (APPLE)
    link_directories(
        /usr/lib
        )
    if (FALSE)
        target_link_libraries(${PROJECT_NAME} 
            -lcrt0.o
            )
    endif ()
elseif (UNIX)
link_directories()
endif ()

