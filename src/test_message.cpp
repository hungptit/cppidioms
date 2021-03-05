#include <cstdlib>

#include "message.hpp"

int main() {
  experiments::MeasureWithSpdlog("Log all measure information using spdlog.")();
  experiments::DimensionWithStdout()();
  return EXIT_SUCCESS;
}
