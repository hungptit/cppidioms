#include "unused_port_posix.h"

int main() {
  std::cout << "Unused port: " << cppidioms::UnusedPort::port() << "\n";
}
