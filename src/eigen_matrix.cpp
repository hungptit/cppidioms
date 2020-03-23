#include "Eigen/Dense"
#include <iostream>
using namespace Eigen;
int main() {
    VectorXf x(6);
    x << 1, 2, 3, 4, 5, 6;
    std::cout << x.transpose() << "\n";
    std::cout << x << "\n";

    // auto y = x.log();
    // std::cout << "log(x)" << y << "\n";

    Matrix3f mx;
    mx << 1, 2, 3, 4, 5, 6, 7, 8, 9;
    std::cout << mx << "\n";

    Matrix3f my;
    // clang-format off
    my << 1, 2, 3
       << 4, 5, 6
       << 7, 8, 9;
    // clang-format on
    std::cout << mx << "\n";
    std::cout << mx + my << "\n";

    // x.array().exp();
    // std::cout << "exp(x)" << x << "\n";
}
