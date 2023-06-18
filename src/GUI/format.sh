#!/bin/bash
set -e
set -x

FILES=$(find src/ -name '*.cpp' -o -name '*.hpp')

clang-format --style=file -i $FILES
