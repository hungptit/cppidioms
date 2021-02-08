find_package(Threads)

# Examples
set(EXECUTABLESS hello_world)
foreach(EXECUTABLE ${EXECUTABLESS})
  add_executable(${EXECUTABLE} ${EXECUTABLE}.cpp)
  target_link_libraries(${EXECUTABLE} PRIVATE Threads::Threads)
  add_test(${EXECUTABLE} ./${EXECUTABLE})
endforeach(EXECUTABLE)

enable_testing()
