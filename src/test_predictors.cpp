#include <cstdlib>

#include "binlog/TextOutputStream.hpp"
#include "binlog/binlog.hpp"
#include "predictors.hpp"

int main() {
  experiments::MeasureWithSpdlog("Log all measure information using spdlog.")();
  experiments::DimensionWithStdout()();

  return EXIT_SUCCESS;
}
