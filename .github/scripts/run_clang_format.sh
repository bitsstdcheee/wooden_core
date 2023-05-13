#!/bin/bash
files=$(git ls-files -- '*.c' '*.h' '*.cpp')
result=0
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
    git diff --no-color > clang-format-ouput.log
    exit 1
fi