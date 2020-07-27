#include <iostream>
#include <memory>

class Base {
 public:
  virtual ~Base() = default;

  void print() const { print_impl(); };

 private:
  virtual void print_impl() const { std::cout << "This is a base class\n"; }
};

class Derived : public Base {
 public:
  virtual ~Derived() = default;

 private:
  virtual void print_impl() const {
    std::cout << "This is the derived class.\n";
  }
};

int main() {
  Base base;
  Derived derived;

  base.print();
  derived.print();

  std::unique_ptr<Base> pt1 = std::make_unique<Base>();
  pt1->print();

  std::unique_ptr<Base> pt2 = std::make_unique<Derived>();
  pt2->print();
}
