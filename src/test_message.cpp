#include <cstdlib>

#include "message.hpp"

int main() {
  experiments::RequestStdout("Request\n")();
  experiments::ResponseStderr()();
  return EXIT_SUCCESS;
}
