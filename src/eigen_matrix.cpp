#include <iostream>

#include "Eigen/Dense"
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
  my = mx.transpose();
  std::cout << "mx:\n" << mx << "\n";
  std::cout << "my:\n" << my << "\n";
  std::cout << "mx + my:\n" << my + mx << "\n";
  my.setIdentity();
  std::cout << "Identity:\n" << my << "\n";
  std::cout << "my[2,2]:\n" << my(2, 2) << "\n";
}
