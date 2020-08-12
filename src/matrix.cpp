#include <iostream>
#include <vector>

template <typename T>
void print(const std::vector<std::vector<T>>& mat) {
  for (auto const& row : mat) {
    for (auto element : row) {
      std::cout << element << " ";
    }
    std::cout << "\n";
  }
}

int main() {
  std::vector<std::vector<int>> data(10, std::vector<int>{1, 2, 3, 4, 5});
  print(data);
  return EXIT_SUCCESS;
}
