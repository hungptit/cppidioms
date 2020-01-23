#include <iostream>

struct Test {
    Test() {
        std::cout << "====> Constructor\n";
    }

    template <typename T>
    Test( T &&) {
        std::cout << "Move/copy constructor\n";
    }

    ~Test() {
        std::cout << "<==== Destructor\n";
    }

    void print(const std::string &msg) {
        std::cout << msg << "\n";
    }
};

Test & create() {
    static Test test;
    return test;
}


int main() {
    create().print("Init");

    {
        create().print("Chaining calls");
    }

    {
        auto test = create();
        test.print("Use auto");
    }
    {
        auto & test = create();
        test.print("Use auto&");
    }

    std::cout << "====> Done\n";
}
