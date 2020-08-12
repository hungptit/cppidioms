#include <cstdint>
#include <iostream>
#include <memory>

struct Test {
  Test() = default;
  ~Test() = default;
  void finish() const { std::cout << "finished\n"; }
  enum MyEnum : uint32_t { NONE = 0, ONE = 1 };
};

struct CustomDeleter {
  void operator()(Test* test) const { test->finish(); }
};

int main() {
  std::unique_ptr<Test> p1(new Test());
  std::unique_ptr<Test, CustomDeleter> p2(new Test(), CustomDeleter());
}
