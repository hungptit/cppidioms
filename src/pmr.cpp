#include <algorithm>
#include <array>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <iterator>
#include <memory_resource>

int main() {
  std::array<char, 64> buffer;
  std::fill_n(buffer.begin(), buffer.size(), '_');
  std::cout << buffer.data() << '\n';

  std::pmr::monotonic_buffer_resource pool{buffer.data(), buffer.size()};

  std::pmr::vector<char> vec{&pool};

  for (char ch = 'a'; ch <= 'z'; ++ch) vec.push_back(ch);

  std::cout << buffer.data() << '\n';
  return EXIT_SUCCESS;
}
