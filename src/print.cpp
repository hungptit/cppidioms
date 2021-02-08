
#include <iostream>
#include <vector>

#include "utilities.hpp"

int main() {
  std::vector<double> dvec = {1, 2, 3, 4, 5};
  std::cout << dvec << "\n";

  std::map<int, std::string> m = {{1, "Hello"}, {2, "Good night"}};
  std::cout << m << "\n";
}
