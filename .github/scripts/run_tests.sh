#!/bin/bash

# 记录不正常的测试
error_tests=()

# 运行测试
for dir in tests/*/; do
  testname=$(basename "$dir")
  executable="./build/tests/bin/test-$testname.exe"

  if [ -x "$executable" ]; then
    echo "Running test: $testname"
    if "$executable"; then
      echo "Test $testname completed successfully."
    else
      echo "Test $testname returned a non-zero exit code or exited abnormally."
      error_tests+=("$testname")
      echo "::error file=$executable,title=Test Failure::$testname test failed."
    fi
  else
    echo "Test $testname executable not found."
  fi
done

# 输出统计信息
if [ ${#error_tests[@]} -eq 0 ]; then
  echo "All tests completed successfully."
  exit 0
else
  echo "Failed tests: ${error_tests[*]}"
  echo "::warning title=Test Failures::Some tests failed. Please check the logs for details."
  exit -1
fi
