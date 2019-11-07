// Type your code here, or load an example.
#include <chrono>
#include <iostream>
#include <memory>
#include <thread>
#include <vector>

struct Counter {
    explicit Counter(const int val) : value(val) {}
    ~Counter() { print(); }
    void print() { std::cout << "Current counter: " << value << "\n"; }
    int value;
};

struct Obj1 {
    Obj1(std::shared_ptr<Counter> cnt) : counter(cnt) {}
    std::shared_ptr<Counter> counter;
    void increase() { ++counter->value; }
};

struct Obj2 {
    Obj2(std::shared_ptr<Counter> cnt) : counter(cnt) {}
    std::shared_ptr<Counter> counter;
    void increase() { ++counter->value; }
};

int main() {
    {
        auto counter = std::make_shared<Counter>(0);

        Obj1 obj1(counter);
        obj1.increase();
        counter->print();

        Obj2 obj2(counter);
        obj2.increase();
        obj1.increase();
        counter->print();
    }

    {
        std::thread t1;
        std::thread t2;
    }
}
