#!/bin/bash
set -e # Use Bash strict mode

printf "Build doctest\n"
./build_using_cmake.sh doctest >/dev/null

printf "Build FMT\n"
./build_using_cmake.sh fmt "-DFMT_DOC=OFF -DFMT_TEST=OFF" >/dev/null

printf "Build benchmark\n"
./build_using_cmake.sh benchmark -DBENCHMARK_ENABLE_TESTING=OFF >/dev/null

printf "Setup Clara\n"
cp src/Clara/include/*.hpp include/
