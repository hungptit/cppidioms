#include <array>
#include <iostream>
#include <limits>

bool ex1(const double x) { return x <= 0.0; }

bool ex2(const double x) {
  constexpr double eps = std::numeric_limits<double>::epsilon();
  return x < eps;
}

bool ex3(const double x) {
  constexpr double eps = std::numeric_limits<double>::epsilon();
  return x >= eps;
}

bool ex4(const double x) { return x > 0; }

int main() {
  const double deps = std::numeric_limits<double>::epsilon();
  const double feps = std::numeric_limits<float>::epsilon();

  std::cout << "Float: " << feps << "\n";
  std::cout << "Double: " << deps << "\n";

  std::cout << "Case 1.1: " << ex1(deps / 2) << "\n";
  std::cout << "Case 1.2: " << ex1(deps) << "\n";
  std::cout << "Case 1.3: " << ex1(2 * deps) << "\n";

  std::cout << "Case 2.1: " << ex2(deps / 2) << "\n";
  std::cout << "Case 2.2: " << ex2(deps) << "\n";
  std::cout << "Case 2.3: " << ex2(2 * deps) << "\n";

  std::cout << "Case 3.1: " << ex3(deps / 2) << "\n";
  std::cout << "Case 3.2: " << ex3(deps) << "\n";
  std::cout << "Case 3.3: " << ex3(2 * deps) << "\n";

  std::cout << "Case 4.1: " << ex4(deps / 2) << "\n";
  std::cout << "Case 4.2: " << ex4(deps) << "\n";
  std::cout << "Case 4.3: " << ex4(2 * deps) << "\n";

  return EXIT_SUCCESS;
}
