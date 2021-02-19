#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>

int main() {
  const double NaN = std::nan("");
  constexpr double inf = std::numeric_limits<double>::infinity();

  // std::cout << "std::hermitel(1, -inf)" << std::hermitel(1, -inf) << "\n";
  // std::cout << "std::hermitel(1, +inf)" << std::hermitel(1, inf) << "\n";
  // std::cout << "std::hermitel(1, NaN)" << std::hermitel(1, NaN) << "\n";
  std::cout << "log(-inf): " << std::log(-inf) << "\n";
  std::cout << "log(inf): " << std::log(inf) << "\n";
  std::cout << "log(NaN): " << std::log(NaN) << "\n";
  std::cout << "log(0): " << std::log(0.0) << "\n";

  return EXIT_SUCCESS;
}
