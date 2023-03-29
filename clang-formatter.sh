#! /bin/sh env
clang-format -i examples/*/*cpp
clang-format -i q*.h q*.cpp
clang-format -i file-parser/*.h file-parser/*.cpp
