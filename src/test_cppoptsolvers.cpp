// Copyright 2020, https://github.com/PatWie/CppNumericalSolvers

#include <iostream>
#include <ostream>

#include "cppoptlib/function.h"
#include "cppoptlib/solver/bfgs.h"
#include "cppoptlib/solver/conjugated_gradient_descent.h"
#include "cppoptlib/solver/gradient_descent.h"
#include "cppoptlib/solver/lbfgs.h"
#include "cppoptlib/solver/lbfgsb.h"
#include "cppoptlib/solver/newton_descent.h"

using FunctionXd = cppoptlib::function::Function<double>;

class Rosenbrock : public FunctionXd {
 public:
  using FunctionXd::hessian_t;
  using FunctionXd::vector_t;

  scalar_t operator()(const vector_t& x) const override {
    const double t1 = (1 - x[0]);
    const double t2 = (x[1] - x[0] * x[0]);
    return t1 * t1 + 100 * t2 * t2;
  }
};

int main() {
  // using Solver = cppoptlib::solver::NewtonDescent<Function>;
  // using Solver = cppoptlib::solver::GradientDescent<Function>;
  // using Solver = cppoptlib::solver::ConjugatedGradientDescent<Function>;
  // using Solver = cppoptlib::solver::Bfgs<Function>;
  // using Solver = cppoptlib::solver::Lbfgs<Rosenbrock>;
  using Solver = cppoptlib::solver::Lbfgsb<Rosenbrock>;

  Rosenbrock f;
  Rosenbrock::vector_t x(2);
  x << -100, 2;

  auto state = f.Eval(x);
  std::cout << "this"
            << "\n";

  std::cout << f(x) << "\n";
  std::cout << state.gradient << "\n";
  std::cout << state.hessian << "\n";

  std::cout << cppoptlib::utils::IsGradientCorrect(f, x) << "\n";
  std::cout << cppoptlib::utils::IsHessianCorrect(f, x) << "\n";

  Solver solver;

  auto [solution, solver_state] = solver.Minimize(f, x);
  std::cout << "argmin " << solution.x.transpose() << "\n";
  std::cout << "f in argmin " << solution.value << "\n";
  std::cout << "iterations " << solver_state.num_iterations << "\n";
  std::cout << "status " << solver_state.status << "\n";

  std::cout << "Solution: " << solution.x.transpose() << "\n";
  std::cout << "f(x): " << f(solution.x) << "\n";

  return 0;
}
