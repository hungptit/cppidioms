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
    # use_clara
)
foreach(executable ${EXECUTABLES})
  add_executable(${executable} ${executable}.cpp)
  target_link_libraries(${executable})
  target_code_coverage(${executable} all auto external)
  target_include_directories(${executable} PRIVATE "${eigen_SOURCE_DIR}"
                                                   "${doctest_SOURCE_DIR}")
  add_test(${executable} ./${executable})
endforeach(executable)

# Hiding the template implementation in the source code.
add_library(message STATIC message.cpp)
add_executable(test_message test_message.cpp)
target_link_libraries(test_message message)
target_code_coverage(test_message all auto external)

# test_libmdbx add_executable(test_libmdbx test_libmdbx.cpp)
# target_link_libraries(test_libmdbx "${EXTERNAL_DIR}/lib/libmdbx-static.a")
# add_test(test_libmdbx ./test_libmdbx)

enable_testing()
