set(TEST_NAME hello)
set(TEST_DESCRIPTION "Hello World 测试")

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
else()
    message("Test ${TEST_NAME} will be ignored")
endif()