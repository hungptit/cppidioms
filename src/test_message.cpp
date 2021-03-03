#include <cstdlib>

#include "message.hpp"

template <>
struct experiments::message<experiments::MessageType::HELLO>;

int main() {
  experiments::message<experiments::MessageType::HELLO> msg1("Hello\n");
  msg1();

  experiments::message<experiments::MessageType::GOODBYE> msg2;
  msg2();

  return EXIT_SUCCESS;
}
