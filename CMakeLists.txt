cmake_policy(SET CMP0048 NEW)
project(
  cppidioms
  VERSION 0.1.0
  LANGUAGES CXX)

cmake_minimum_required(VERSION 3.15)

enable_testing()

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif()

# Use C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(POSITION_INDEPENDENT_CODE ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(AddCXXCompilerFlag)
include(CXXFeatureCheck)

include(FetchContent)

# Add doctest
FetchContent_Declare(
  doctest
  GIT_REPOSITORY https://github.com/onqtam/doctest.git
  GIT_TAG 2.4.4)
set(DOCTEST_WITH_TESTS OFF)
FetchContent_MakeAvailable(doctest)

# Add spdlog
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.8.2)
FetchContent_MakeAvailable(spdlog)

FetchContent_Declare(
  binlog
  GIT_REPOSITORY https://github.com/morganstanley/binlog.git
  GIT_TAG 2020-04-26)
FetchContent_MakeAvailable(binlog)

# Add benchmark
FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.5.2)
set(BENCHMARK_ENABLE_TESTING OFF)
set(BENCHMARK_ENABLE_GTEST_TESTS OFF)
set(BENCHMARK_ENABLE_ASSEMBLY_TEST OFF)
FetchContent_MakeAvailable(benchmark)

# Eigen
FetchContent_Declare(
  eigen
  GIT_REPOSITORY https://gitlab.com/libeigen/eigen.git
  GIT_TAG master)
set(BUILD_TESTING OFF)
FetchContent_Populate(eigen)

# fmt
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 7.1.3)
set(BUILD_TESTING OFF)

set(FMT_DOC OFF)
set(FMT_TEST OFF)
FetchContent_MakeAvailable(fmt)

# boost
FetchContent_Declare(
  boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG master)
set(BOOST_ENABLE_CMAKE ON)
FetchContent_MakeAvailable(boost)

# Add cmake-scripts
FetchContent_Declare(
  cmake_scripts
  GIT_REPOSITORY https://github.com/StableCoder/cmake-scripts.git
  GIT_TAG main
  GIT_SHALLOW TRUE)

FetchContent_Populate(cmake_scripts)

# Add libmdbx FetchContent_Declare( libmdbx GIT_REPOSITORY
# https://github.com/erthink/libmdbx.git GIT_TAG v0.9.2)

# set(MDBX_INSTALL_STATIC ON) FetchContent_MakeAvailable(libmdbx)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/_deps/cmake_scripts-src/;")
include(c++-standards)
include(code-coverage)
include(sanitizers)
include(tools)
include(dependency-graph)

add_compile_options(-pedantic)
add_compile_options(-pedantic-errors)

# Add sub-directories
add_subdirectory(src)
add_subdirectory(thread)

# Formating and linting all related files
file(GLOB_RECURSE SRCS_AND_HDRS CONFIGURE_DEPENDS src/*.[ch]pp src/*.h
     thread/*cpp)
find_program(CLANG_FORMAT NAMES clang-format)
add_custom_command(
  OUTPUT .format_cpp_stamp
  DEPENDS ${SRCS_AND_HDRS}
  COMMAND ${CLANG_FORMAT} -i ${SRCS_AND_HDRS}
  COMMAND touch .format_cpp_stamp
  COMMENT "Format C++ files with clang-format."
  VERBATIM)

set(CMAKE_FILES "CMakeLists.txt" "src/CMakeLists.txt" "thread/CMakeLists.txt")
find_program(CMAKE_FORMAT NAMES cmake-format)
if(${CMAKE_FORMAT} STREQUAL "CMAKE_FORMAT-NOTFOUND")
  add_custom_command(
    OUTPUT .format_cmake_stamp
    DEPENDS ${CMAKE_FILES}
    COMMAND touch .format_cmake_stamp
    COMMENT "Skip formatting CMake files."
    VERBATIM)
else()
  add_custom_command(
    OUTPUT .format_cmake_stamp
    DEPENDS ${CMAKE_FILES}
    COMMAND cmake-format -i ${CMAKE_FILES}
    COMMAND touch .format_cmake_stamp
    COMMENT "Format CMake files with cmake-format."
    VERBATIM)
endif()

file(GLOB SH_SRCS 3p/*.sh)
find_program(SHFORMAT NAMES shformat)
if(${SHFORMAT} STREQUAL "SHFORMAT-NOTFOUND")
  add_custom_command(
    OUTPUT .format_bash_stamp
    DEPENDS ${SH_SRCS}
    COMMAND touch .format_bash_stamp
    COMMENT "Skip formatting Bash scripts."
    VERBATIM)
else()
  add_custom_command(
    OUTPUT .format_bash_stamp
    DEPENDS ${SH_SRCS}
    COMMAND ${SHFORMAT} -i 2 -ci -w ${SH_SRCS}
    COMMAND touch .format_bash_stamp
    COMMENT "Format Bash scripts with shformat."
    VERBATIM)
endif()

add_custom_target(
  format
  DEPENDS .format_cpp_stamp .format_cmake_stamp
  COMMENT "Format Bash, C++, and CMake files.")
