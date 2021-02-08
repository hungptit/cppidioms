find_package(Threads)

# Examples
set(EXECUTABLES hello_world)
foreach(executable ${EXECUTABLES})
  add_executable(${executable} ${executable}.cpp)
  target_link_libraries(${executable} PRIVATE Threads::Threads)
  add_test(${executable} ./${executable})
endforeach()

enable_testing()
