#include <cstdlib>

#include "message.hpp"

int main() {
  experiments::Request("Request\n")();
  experiments::Response()();
  return EXIT_SUCCESS;
}
