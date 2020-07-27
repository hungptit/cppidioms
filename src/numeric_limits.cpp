#include <cmath>
#include <iostream>
#include <limits>

int main() {
  const double max = std::numeric_limits<double>::max();
  const double inf = std::numeric_limits<double>::infinity();

  if (inf > max) std::cout << inf << " is greater than " << max << '\n';
  std::cout << inf << "Infinity is " << (std::isnan(inf) ? "" : "not ")
            << "NaN\n";
  std::cout << -inf << "-Infinity is " << (std::isnan(-inf) ? "" : "not ")
            << "NaN\n";

  const double val = 1.0;
  std::cout << "val - inf = " << val - inf << "\n";
  std::cout << "-inf + val = " << (-inf) + val << "\n";
  std::cout << "-inf + inf = " << (-inf) + (+inf) << "\n";
  std::cout << "val + inf = " << val + (+inf) << "\n";
}
