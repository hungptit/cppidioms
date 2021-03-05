#include "message.hpp"

#include <iostream>
#include <string>

#include "spdlog/spdlog.h"

namespace experiments {

void detail::Logger<detail::OutputType::SPDLOG>::log(const std::string& msg) {
  spdlog::info("Use spdlog");
  spdlog::info(msg);
};

void detail::Logger<detail::OutputType::STDOUT>::log(const std::string& msg) {
  std::cout << "Use std::cout\n";
  std::cout << msg << "\n";
}

}  // namespace experiments
