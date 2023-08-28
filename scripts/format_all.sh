
style="Google"
source_files=$(find src -type f -regex ".*\.\(cpp\|cxx\|h\|hpp\)")
test_files=$(find tests -type f -regex ".*\.\(cpp\|cxx\|h\|hpp\)")

if [ ! -z "$source_files" ]; then
    clang-format -i --style=$style $source_files
fi

if [ ! -z "$test_files" ]; then
    clang-format -i --style=$style $test_files
fi

clang-format -i --style=$style *.cpp