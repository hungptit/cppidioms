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

template <typename T> void exec(const T &value) {
    static_assert(std::is_base_of<A, T>::value, "It works!");
    value.print();
}

int main() {
    A a;
    B b;
    C c;

    exec(a);
    // exec(b);
    exec(c);

    return EXIT_SUCCESS;
}
