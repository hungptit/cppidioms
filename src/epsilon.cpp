#include <iostream>
#include <limits>
int main() {
  std::cout << "Float: " << std::numeric_limits<float>::epsilon() << "\n";
  std::cout << "Double: " << std::numeric_limits<double>::epsilon() << "\n";
  return EXIT_SUCCESS;
}
