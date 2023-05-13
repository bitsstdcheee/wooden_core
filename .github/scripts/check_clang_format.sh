#!/bin/bash
echo "当前脚本工作目录: $(pwd)"
if [[ -n "$GITHUB_ACTIONS" ]]; then
    files=$(git ls-files -- *.c *.h *.cpp)
    # Github Actions 的默认工作目录在项目根目录
else
    files=$(git ls-files -- ../../*.c ../../*.h ../../*.cpp)
fi
result=0
rm -f ./clang-format/clang-format-output.log
rm -f ./clang-format/lang-format-error.log
mkdir -p ./clang-format
for f in $files; do
    echo "进行代码文件 ${f} 的格式检查"
    command_failed=0
    clang-format -style=file --sort-includes -i --dry-run -Werror $f || command_failed=1
    result=$(( $command_failed|$result ))
    clang-format -style=file --sort-includes -i --dry-run -Werror $f >> ./clang-format/clang-format-output.log
    clang-format -style=file --sort-includes -i --dry-run -Werror $f 2>> ./clang-format/clang-format-error.log
    if [[ "$command_failed" == "1" ]]; then
        echo "❌代码文件 ${f} 格式检查不通过"
    else
        echo "✅代码文件 ${f} 格式检查通过"
    fi
    result=$(($command_failed|$result))
done
exit $result
