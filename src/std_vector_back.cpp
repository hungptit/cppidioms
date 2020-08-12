#include <iostream>
#include <vector>

// Type your code here, or load an example.
void print() {
  auto output = [](const std::vector<int>& data) {
    std::cout << "\n";
    for (auto item : data) std::cout << item << ", ";
    std::cout << "\n";
  };
  std::vector<int> data{1, 2, 3, 4};
  output(data);
  data.back() = 6;
  output(data);
}

int main() { print(); }
