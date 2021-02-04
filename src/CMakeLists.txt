# Unittests
set(CPP_FILES
    accumulate
    arg_parser
    avoid_boost_optional
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
    shared_ptr
    singleton
    stats
    std_vector_back
    stream_operator
    terminate_flush
    test_ifstream
    test_constexpr
    unique_ptr_vector
    unique_ptr
    polynomials
    # use_clara
)
foreach(src_file ${CPP_FILES})
  add_executable(${src_file} ${src_file}.cpp)
  target_link_libraries(${src_file})
  target_code_coverage(${src_file} all auto external)
  add_test(${src_file} ./${src_file})
endforeach(src_file)

# test_libmdbx add_executable(test_libmdbx test_libmdbx.cpp)
# target_link_libraries(test_libmdbx "${EXTERNAL_DIR}/lib/libmdbx-static.a")
# add_test(test_libmdbx ./test_libmdbx)

enable_testing()
