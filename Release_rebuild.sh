#!/bin/bash

rm -rf build
cmake -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_BUILD_TYPE=Release -B build -G "Ninja"
echo -e "\n============================================================\nSUCCESSFUL BUILD\n==================================================================\n"
cmake --build build
