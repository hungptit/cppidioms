#include <cstdlib>
#include <iostream>
#include <memory>

int main() {
  std::unique_ptr<int> val;
  std::cout << (val.get() ? "not null" : "null") << "\n";
  return EXIT_SUCCESS;
}
