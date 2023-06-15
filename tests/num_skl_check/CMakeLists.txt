###  设置区
set(TEST_NAME NUM_SKL)
set(TEST_DESCRIPTION "检查 wooden_judge.cpp 中 NUM_SKL 和 NUL_SKL_M 的一致性")
set(TEST_USES_ROOT TRUE)   # 是否使用 wooden 文件
###  设置区

set(EXEC_NAME test-${TEST_NAME})
file(GLOB CPP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")
if(TEST_USES_ROOT)
    set(CPP_SOURCES "${CPP_SOURCES};${GLOBAL_SOURCES_CORE}")
endif()

option(DISABLE_TEST_${TEST_NAME}, "Disable ${TEST_NAME} test" OFF)
if(NOT DISABLE_TEST_${TEST_NAME})
    add_executable(${EXEC_NAME} ${CPP_SOURCES})
    if(TEST_USES_ROOT)
        target_include_directories(${EXEC_NAME} PUBLIC ${GLOBAL_INCLUDE_DIRECTORY})
    endif()
    add_dependencies(Tests ${EXEC_NAME})
    set_target_properties(${EXEC_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests/bin"
    )
    target_link_libraries(${EXEC_NAME} GTest::gtest_main)
    # gtest_discover_tests(${EXEC_NAME})
    add_test(NAME ${TEST_NAME} COMMAND ${EXEC_NAME})
    message("测试 ${EXEC_NAME} 已添加")
else()
    message("测试 ${TEST_NAME} 将会被忽略")
endif()