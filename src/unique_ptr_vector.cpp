#include <iostream>
#include <memory>
#include <string>
#include <vector>

struct Base {
  std::string name = "Hello";
  virtual void print() = 0;
  virtual ~Base(){};
};

struct A : public Base {
  virtual void print() final { std::cout << "A: " << name << "\n"; }
  virtual ~A() = default;
};

struct B : public Base {
  virtual ~B() = default;
  virtual void print() final { std::cout << "B: " << name << "\n"; }
};

struct C : public Base {
  virtual ~C() = default;
  virtual void print() final { std::cout << "C: " << name << "\n"; }
};

int main() {
  // Use initializer list
  const auto list1 = {std::unique_ptr<Base>(new A()),
                      std::unique_ptr<Base>(new B()),
                      std::unique_ptr<Base>(new C())};
  for (auto it = list1.begin(); it != list1.end(); ++it) {
    (*it)->print();
  }

  std::vector<std::unique_ptr<Base>> list3;
  list3.emplace_back(new A());
  list3.emplace_back(new B());
  list3.emplace_back(new C());
  for (auto it = list3.begin(); it != list3.end(); ++it) {
    (*it)->print();
  }

  // TODO: This does not work. Is there any elegant solution for vector?
  // std::vector<std::unique_ptr<Base>> list2{std::unique_ptr<Base>(new A()),
  // std::unique_ptr<Base>(new B()),
  //                                          std::unique_ptr<Base>(new C())};
  // for (auto it = list1.begin(); it != list1.end(); ++it) {
  //     (*it)->print();
  // }
}
