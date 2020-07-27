#include <iostream>

#include "test.hpp"

struct Base {
  Base() : name() {}

  Base(const std::string& val) : name(val) {}

  Base(const Base& val) : name(val.name) { std::cout << "Copy constructor\n"; }

  Base(Base&& val) : name(std::move(val.name)) {
    std::cout << "Move constructor\n";
  }

  std::string name;
};

Base create1(const Base& val) { return Base(val); }

template <typename T>
T create2(T&& val) {
  return T(std::forward<T>(val));
}

int myfunc(const int value = 0) { return value * 2; }

int main() {
  Base x;
  Base y = x;

  {
    std::cout << "create1\n";
    create1(x);
    create1(Base("Hello"));
  }

  {
    std::cout << "create2\n";
    create2(std::move(x));
    create2(Base("Hello"));
  }
}

// Expected output:
// mac-hdang:src hdang$ ./move_semantics
// Copy constructor
// create1
// Copy constructor
// Copy constructor
// create2
// Move constructor
// Move constructor
