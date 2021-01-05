#include <array>
#include <exception>
#include <iostream>

int main() {
  constexpr std::array<int, 5> x{1, 2, 3, 4, 5};
  for (auto item : x) std::cout << item << " ";
  std::cout << "\n";
}
