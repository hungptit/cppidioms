#include "predictors.hpp"

#include <binlog/TextOutputStream.hpp>
#include <iostream>
#include <string>

#include "binlog/binlog.hpp"
#include "spdlog/spdlog.h"

namespace experiments {

void detail::Logger<detail::OutputType::SPDLOG>::log(const std::string& msg) {
  spdlog::info("Use spdlog.");
  spdlog::info(msg);
};

void detail::Logger<detail::OutputType::STDOUT>::log(const std::string& msg) {
  BINLOG_INFO("Use binlog.");
  BINLOG_INFO("{}", msg);
  binlog::TextOutputStream output(std::cout);
  binlog::consume(output);
}

}  // namespace experiments
