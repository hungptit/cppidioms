#include <iostream>

#include "Eigen/Dense"
using namespace Eigen;
int main() {
  Matrix2d a;
  a << 1, 2, 3, 4;
  Vector3d v(1, 2, 3);
  std::cout << "a * 2.5 =\n" << a * 2.5 << std::endl;
  std::cout << "0.1 * v =\n" << 0.1 * v << std::endl;
  std::cout << "Doing v *= 2;" << std::endl;

  v *= 2.0;
  std::cout << "Now v =\n" << v << std::endl;

  // Does not work
  v.array() -= 2;

  // Does xwork
  v.array() -= 2;
  std::cout << "Now v =\n" << v << std::endl;

  Vector3d x(1, 2, 3);
  x.array().log();
  std::cout << x << "\n";
}
