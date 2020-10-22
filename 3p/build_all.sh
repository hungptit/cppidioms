#!/bin/bash
set -e # Use Bash strict mode

printf "Build FMT\n"
./build_using_cmake.sh fmt -DFMT_DOC=OFF -DFMT_TEST=OFF >/dev/null

printf "Build benchmark\n"
./build_using_cmake.sh benchmark -DBENCHMARK_ENABLE_TESTING=OFF >/dev/null

printf "Setup Clara\n"
mkdir -pv include/clara
cp -rv src/Clara/include/*.hpp include/clara

printf "Build doctest\n"
cp -rv src/doctest/doctest include/

printf "Build libmdbx\n"
./build_using_cmake.sh libmdbx -DMDBX_INSTALL_STATIC=ON -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_C_COMPILER=clang >/dev/null

printf "Install cppoptlib\n"
cp -rv src/CppNumericalSolvers/include/cppoptlib include/
