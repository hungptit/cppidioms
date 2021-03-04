#include "message.hpp"

#include <iostream>
#include <string>

namespace experiments {

void detail::Console<detail::OutputType::STDOUT>::write(
    const std::string& msg) {
  std::cout << msg;
};
    
void detail::Console<detail::OutputType::STDERR>::write(
    const std::string& msg) {
  std::cerr << msg;
}

}  // namespace experiments
