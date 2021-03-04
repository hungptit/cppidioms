#include "message.hpp"

#include <iostream>
#include <string>

namespace experiments {

void detail::Logger<detail::OutputType::STDOUT>::log(const std::string& msg) {
  std::cout << msg;
};

void detail::Logger<detail::OutputType::STDERR>::log(const std::string& msg) {
  std::cerr << msg;
}

}  // namespace experiments
