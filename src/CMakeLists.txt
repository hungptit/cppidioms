if(MSVC)
  add_compile_options(/W4 /WX)
else()
  add_cxx_compiler_flag(-Wall)
  add_cxx_compiler_flag(-Wextra)
  add_cxx_compiler_flag(-pedantic)
  add_cxx_compiler_flag(-Werror)

  # add_cxx_compiler_flag(-static)  # add_cxx_compiler_flag(-lto)
endif()

add_cxx_compiler_flag(-DFMT_HEADER_ONLY)

# Unittests
set(EXECUTABLES
    accumulate
    # arg_parser
    avoid_boost_optional
    call_once
    code_warrior
    custom_deleter
    eigen_matrix
    eigen_ops
    enable_if
    enum_values
    epsilon
    function_arg_lifetime
    generate
    get_line
    get_unused_port
    interface_class
    is_base_of
    map_erase
    matrix
    misuse_smart_ptr
    move_semantics
    numeric_limits
    # pmr
    print
    shared_ptr
    singleton
    stats
    std_vector_back
    stream_operator
    struct_constructor
    terminate_flush
    test_ifstream
    test_constexpr
    unique_ptr_vector
    unique_ptr
    polynomials
    yas_example
    # use_clara
)
foreach(executable ${EXECUTABLES})
  add_executable(${executable} ${executable}.cpp)
  target_link_libraries(${executable})
  target_code_coverage(${executable} all auto external)
  target_include_directories(
    ${executable} PRIVATE "${eigen_SOURCE_DIR}" "${doctest_SOURCE_DIR}"
                          "${yas_SOURCE_DIR}/include")
  add_test(${executable} ./${executable})
endforeach(executable)

# Hiding the template implementation in the source code.
add_library(mylib STATIC predictors.cpp)
target_include_directories(mylib PRIVATE ${spdlog_SOURCE_DIR}/include/
                                         ${binlog_SOURCE_DIR}/include/)
target_link_libraries(mylib PRIVATE spdlog::spdlog binlog::binlog)

add_executable(test_predictors test_predictors.cpp)
target_link_libraries(test_predictors mylib)
target_include_directories(
  test_predictors PRIVATE ${spdlog_SOURCE_DIR}/include/
                          ${binlog_SOURCE_DIR}/include/)
target_code_coverage(test_predictors all auto external)

# test_libmdbx add_executable(test_libmdbx test_libmdbx.cpp)
# target_link_libraries(test_libmdbx "${EXTERNAL_DIR}/lib/libmdbx-static.a")
# add_test(test_libmdbx ./test_libmdbx)

enable_testing()
