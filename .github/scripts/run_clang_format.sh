#!/bin/bash
echo "当前脚本工作目录: $(pwd)"
if [[ -n "$GITHUB_ACTIONS" ]]; then
    files=$(git ls-files -- *.c *.h *.cpp)
    # Github Actions 的默认工作目录在项目根目录
else
    files=$(git ls-files -- ../../*.c ../../*.h ../../*.cpp)
fi
result=0
rm -f ./clang-format/clang-format-run.log
mkdir -p ./clang-format
for f in $files; do
    echo "进行代码文件 ${f} 的格式检查"
    # result=$command_failed|$result
    clang-format -style=file --sort-includes -i $f
done

export GIT_PAGER=cat
diff=$(git diff --color --color-words)
# diffno=$(git diff --no-color)
if [ -z "$diff" ]; then
    echo "✅没有需要更改的代码"
    exit 0
else
    echo "❌代码不符合格式, 需要更改"
    git diff --color --color-words
    git diff --no-color > ./clang-format/clang-format-run.log
    exit 1
fi