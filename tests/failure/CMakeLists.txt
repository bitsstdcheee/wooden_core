set(TEST_NAME failure)
set(TEST_DESCRIPTION "失败测试")

set(EXEC_NAME test-${TEST_NAME})
file(GLOB CPP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

option(DISABLE_TEST_${TEST_NAME}, "Disable ${TEST_NAME} test" OFF)
if(NOT DISABLE_TEST_${TEST_NAME})
    add_executable(${EXEC_NAME} ${CPP_SOURCES})
    add_dependencies(Tests ${EXEC_NAME})
    set_target_properties(${EXEC_NAME} PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests/bin"
    )
    target_link_libraries(${EXEC_NAME} GTest::gtest_main)
    gtest_discover_tests(${EXEC_NAME})
    message("测试 ${EXEC_NAME} 已添加")
else()
    message("测试 ${TEST_NAME} 将会被忽略")
endif()