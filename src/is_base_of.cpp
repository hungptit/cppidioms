
#include <cstdlib>
#include <iostream>
#include <type_traits>

struct A {
  void print() const { std::cout << "Class A\n"; }
};

struct B {
  void print() const { std::cout << "Class B\n"; }
};

struct C : public A {
  void print() const { std::cout << "Class C\n"; }
};

template <typename T>
void exec_v1(const T& value) {
  static_assert(std::is_base_of<A, T>::value, "It works!");
  value.print();
}

template <typename T,
          typename std::enable_if_t<std::is_base_of<A, T>::value, int> = 0>
void exec_v2(const T& value) {
  value.print();
}

int main() {
  A a;
  // B b;
  C c;

  exec_v1<A>(a);
  // exec(b);
  exec_v1(c);
  exec_v2(c);

  return EXIT_SUCCESS;
}
