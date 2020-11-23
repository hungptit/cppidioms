#include <iostream>
#include <memory>
#include <regex>

auto use_after_free(const size_t argc) {
  int* array = new int[100];
  delete[] array;
  return array[argc];  // BOOM
}

int main() { use_after_free(1U); }
