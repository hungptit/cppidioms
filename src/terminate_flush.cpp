#include <cstdlib>
#include <iostream>

struct MyLog {
  MyLog(const std::string& header) : data(header) {}
  ~MyLog() { std::cout << "data" << std::endl; }

  void log(const std::string& msg) { data.append(msg); }
  std::string data = {};
};

int main() {
  MyLog log("Test");
  int val = 0;
  std::cin >> val;
  return EXIT_SUCCESS;
}
