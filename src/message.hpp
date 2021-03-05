#pragma once

#include <iostream>
#include <string>

namespace experiments {

namespace detail {

enum class OutputType { STDOUT, SPDLOG };

template <OutputType>
struct Logger;

// We can hide the implementation in the library because everything is known
// at the compile time.
template <>
struct Logger<OutputType::STDOUT> {
  static void log(const std::string& msg);
};

template <>
struct Logger<OutputType::SPDLOG> {
  static void log(const std::string& msg);
};

}  // namespace detail

using StdoutConsole = detail::Logger<detail::OutputType::STDOUT>;
using SpdlogConsole = detail::Logger<detail::OutputType::SPDLOG>;

enum class PredictorType { INVALID, MEASURE, DIMENSION };

template <PredictorType, typename Logger = StdoutConsole>
class Predictor;

template <typename Logger>
class Predictor<PredictorType::MEASURE, Logger> {
 public:
  explicit Predictor(std::string&& str) : msg(std::move(str)) {}
  void operator()() { Logger::log(msg); }

 private:
  std::string msg;
};

template <typename Logger>
class Predictor<PredictorType::DIMENSION, Logger> {
 public:
  void operator()() { Logger::log(body); }

 private:
  const std::string body = "Log all dimension information using std::cout";
};

using DimensionWithStdout = Predictor<PredictorType::DIMENSION, StdoutConsole>;
using MeasureWithSpdlog = Predictor<PredictorType::MEASURE, SpdlogConsole>;

}  // namespace experiments
