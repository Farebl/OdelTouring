#!/bin/bash

rm -rf build
cmake -DCMAKE_CXX_COMPILER=clang++ -B build -G "Ninja"
echo -e "\n============================================================\nSUCCESSFUL BUILD\n==================================================================\n"
cmake --build build
