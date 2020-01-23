#include <memory>
#include <iostream>

struct Object {
    Object() {
        std::cout << "Constructor\n";
    }

    ~Object() {
        std::cout << "Destructor\n";
    }

    void print() const {
        std::cout << "Print out something here\n";
    }
};

std::unique_ptr<Object> create() {
    return std::make_unique<Object>();
}

void test(const Object* ptr) {
    ptr->print();
}

int main() {
    test(create().get());
}
