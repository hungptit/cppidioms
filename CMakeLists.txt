cmake_policy(SET CMP0048 NEW)
project(
  cppidioms
  VERSION 0.1.0
  LANGUAGES CXX)
cmake_minimum_required(VERSION 3.15)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Use C++ 17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
  set(CMAKE_CXX_COMPILER_LAUNCHER ${CCACHE_PROGRAM})
endif()

set(POSITION_INDEPENDENT_CODE ON)

# Add doctest
FetchContent_Declare(
  doctest
  GIT_REPOSITORY https://github.com/onqtam/doctest.git
  GIT_TAG 2.4.4
  GIT_SHALLOW TRUE)

set(DOCTEST_WITH_TESTS OFF)
FetchContent_MakeAvailable(doctest)

# Add benchmark
FetchContent_Declare(
  benchmark
  GIT_REPOSITORY https://github.com/google/benchmark.git
  GIT_TAG v1.5.2
  GIT_SHALLOW TRUE)

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

# Add cmake-scripts
FetchContent_Declare(
  cmake_scripts
  GIT_REPOSITORY https://github.com/StableCoder/cmake-scripts.git
  GIT_TAG main
  GIT_SHALLOW TRUE)

FetchContent_MakeAvailable(cmake_scripts)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/_deps/cmake_scripts-src/;")
include(c++-standards)
include(code-coverage)
include(sanitizers)
include(tools)
include(dependency-graph)

add_code_coverage_all_targets(EXCLUDE 3p/* unittests/solver_basic_tests.cpp)

# Enable other flags add_compiler_options(-std=c++17)
# add_compiler_options(-Wall) add_compiler_options(-pedantic)
# add_compiler_options(-pedantic-errors) add_compiler_options(-fstrict-aliasing)

# if(HAVE_CXX_FLAG_FSTRICT_ALIASING) add_compiler_options(-Wstrict-aliasing)
# endif()

# if(HAVE_WTHREAD_SAFETY) add_definitions(-DHAVE_WTHREAD_SAFETY)
# cxx_feature_check(THREAD_SAFETY_ATTRIBUTES) endif()

# # add_compile_options(--fno-rtti)

# # Customized flags add_compiler_options(-DFMT_HEADER_ONLY)
# add_compiler_options(-DCEREAL_RAPIDJSON_HAS_CXX11_RVALUE_REFS)

# # Build using static libraries to reduce dependency.
# add_compiler_options(-flto)

# if(NOT USE_SANITIZER) add_compiler_options(-static) endif()

# Include folders
include_directories("_deps/eigen-src/")
include_directories("_deps/doctest-src/")

# Add libraries
find_library(LIB_FMT libfmt.a "${EXTERNAL_DIR}/lib" NO_DEFAULT_PATH)

# Add sub-directories
add_subdirectory(src)

# Formating and linting all related files
file(GLOB_RECURSE SRCS_AND_HDRS src/*.cpp src/*.h)
find_program(CLANG_FORMAT NAMES clang-format)
add_custom_command(
  OUTPUT .fmt_cpp_stamp
  DEPENDS ${SRCS_AND_HDRS}
  COMMAND ${CLANG_FORMAT} -i ${SRCS_AND_HDRS}
  COMMAND touch .fmt_cpp_stamp
  COMMENT "Format C++ files with clang-format."
  VERBATIM)

file(GLOB CMAKE_FILES CMakeLists.txt src/CMakeLists.txt)
find_program(CMAKE_FORMAT NAMES cmake-format)
if(${CMAKE_FORMAT} STREQUAL "CMAKE_FORMAT-NOTFOUND")
  add_custom_command(
    OUTPUT .fmt_cmake_stamp
    DEPENDS ${CMAKE_FILES}
    COMMAND touch .fmt_cmake_stamp
    COMMENT "Skip formatting CMake files."
    VERBATIM)
else()
  add_custom_command(
    OUTPUT .fmt_cmake_stamp
    DEPENDS ${CMAKE_FILES}
    COMMAND cmake-format -i ${CMAKE_FILES}
    COMMAND touch .fmt_cmake_stamp
    COMMENT "Format CMake files with cmake-format."
    VERBATIM)
endif()

file(GLOB SH_SRCS 3p/*.sh)
find_program(SHFMT NAMES shfmt)
if(${SHFMT} STREQUAL "SHFMT-NOTFOUND")
  add_custom_command(
    OUTPUT .fmt_bash_stamp
    DEPENDS ${SH_SRCS}
    COMMAND touch .fmt_bash_stamp
    COMMENT "Skip formatting Bash scripts."
    VERBATIM)
else()
  if(UNIX AND NOT APPLE)
    add_custom_command(
      OUTPUT .fmt_bash_stamp
      DEPENDS ${SH_SRCS}
      COMMAND ${SHFMT} -i 2 -ci -w ${SH_SRCS}
      COMMAND touch .fmt_bash_stamp
      COMMENT "Format Bash scripts with shfmt."
      VERBATIM)
  else()
    add_custom_command(
      OUTPUT .fmt_bash_stamp
      DEPENDS ${SH_SRCS}
      COMMAND touch .fmt_bash_stamp
      COMMENT "Skip formatting Bash scripts."
      VERBATIM)
  endif()
endif()

add_custom_target(
  fmt
  DEPENDS .fmt_bash_stamp .fmt_cpp_stamp .fmt_cmake_stamp
  COMMENT "Format Bash, C++, and CMake files.")

add_custom_command(
  OUTPUT .lint_shellcheck_stamp
  DEPENDS ${SH_SRCS}
  COMMAND shellcheck ${SH_SRCS}
  COMMAND touch .lint_shellcheck_stamp
  COMMENT "Lint Bash files with shellcheck.")

add_custom_command(
  OUTPUT .lint_cmake_stamp
  DEPENDS ${CMAKE_FILES}
  COMMAND cmake-lint ${CMAKE_FILES}
  COMMAND touch .lint_cmake_stamp
  COMMENT "Lint CMake files with cmake-lint.")

add_custom_target(
  lint ALL
  DEPENDS .lint_shellcheck_stamp .lint_cmake_stamp
  COMMENT "Lint Bash and CMake files.")

enable_testing()
