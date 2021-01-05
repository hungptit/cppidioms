#include <cmath>
#include <cstdlib>
#include <iostream>
#include <limits>

int main() {
    const double NaN = std::nan("");
    constexpr double inf = std::numeric_limits<double>::infinity();

    std::cout << "std::hermitel(1, -inf)" << std::hermitel(1, -inf) << "\n";
    std::cout << "std::hermitel(1, +inf)" << std::hermitel(1, inf) << "\n";
    std::cout << "std::hermitel(1, NaN)"<< std::hermitel(1, NaN) << "\n";
    std::cout << "log(-inf): " << std::log(-inf) << "\n";
    std::cout << "log(inf): " << std::log(inf) << "\n";
    std::cout << "log(inf): " << std::log(std::numeric_limits<double>::epsilon()) << "\n";
    std::cout << "log(inf): " << std::log(-0) << "\n";
    std::cout << "log(inf): " << std::log(0) << "\n";
    
    return EXIT_SUCCESS;
}
