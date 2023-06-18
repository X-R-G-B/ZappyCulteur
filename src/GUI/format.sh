#!/bin/bash
set -e
set -x

clang-format -i -style=file **.cpp **.hpp
