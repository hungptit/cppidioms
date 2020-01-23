#include <type_traits>
#include <iostream>

template <typename T, std::enable_if_t<std::is_floating_point<T>::value, int> = 0> void print(const T value) {
    std::cout << "Floating point type: " << value << "\n";
}

template <typename T, std::enable_if_t<!std::is_floating_point<T>::value, int> = 0> void print(const T value) {
    std::cout << "Other type: " << value << "\n";
}

int main() {
    print(std::string("Hello"));
    print(1);
    print(1.0f);
    print(1e0);
}
