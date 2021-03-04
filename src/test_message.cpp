#include <cstdlib>

#include "message.hpp"

int main() {
  experiments::MeasureStdout("Do something with a measure\n")();
  experiments::DimensionStderr()();
  return EXIT_SUCCESS;
}
