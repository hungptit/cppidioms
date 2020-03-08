#include <benchmark/benchmark.h>
#include <iostream>
#include <memory>

namespace {
    struct A {
        explicit A(int val) : value(val){};
        explicit A() : value(0){};
        int getValue1() const { return value; }
        int getValue2() const { return value * 2; }
        int getValue3() const { return value * 3; }
        int value = 0;
    };

    struct B {
        B(int val) { data = std::make_shared<A>(1); }
        std::shared_ptr<A> getData() { return data; }
        std::shared_ptr<A> data;
    };

    struct C {
        C(int val) { data = std::make_shared<A>(1); }
        std::shared_ptr<A> getData() { return data; }
        std::shared_ptr<A> data;
    };
} // namespace

std::shared_ptr<B> data1 = std::make_shared<B>(2);

int use_shared_ptr(std::shared_ptr<B> val) {
    return val->getData()->getValue1() + val->getData()->getValue2() + val->getData()->getValue3();
}

int use_shared_ptr_with_cache(std::shared_ptr<B> val) {
    auto const &obj = val->getData();
    return obj->getValue1() + obj->getValue2() + obj->getValue3();
}

int use_unique_ptr_with_cache(std::unique_ptr<B> data) {
    auto const &obj = data->getData();
    return obj->getValue1() + obj->getValue2() + obj->getValue3();
}

// int use_reference(const B &obj) { return obj.getValue1() + obj.getValue2() + obj.getValue3(); }

// BENCHMARK(use_shared_ptr);
// BENCHMARK(use_shared_ptr_with_cache);
// BENCHMARK(use_unique_ptr_with_cache);
// BENCHMARK(use_reference);

BENCHMARK_MAIN();
