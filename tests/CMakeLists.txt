include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip)
FetchContent_MakeAvailable(googletest)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

enable_testing()

file(GLOB CPP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

foreach (CPP_SOURCE ${CPP_SOURCES})
    # 获取源文件名（不包含路径）
    get_filename_component(SOURCE_NAME ${CPP_SOURCE} NAME_WE)
    # 生成目标文件
    add_executable(test-${SOURCE_NAME} ${CPP_SOURCE})
    target_link_libraries(test-${SOURCE_NAME} GTest::gtest_main)
    gtest_discover_tests(test-${SOURCE_NAME})
    message(STATUS "已添加测试: test-${SOURCE_NAME}")
endforeach (CPP_SOURCE ${CPP_SOURCES})