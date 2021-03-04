#pragma once

#include <iostream>
#include <string>

namespace experiments {

namespace detail {

enum class OutputType { STDOUT, STDERR };

template <OutputType>
struct Logger;

// We can hide the implementation in the library because everything is known
// at the compile time.
template <>
struct Logger<OutputType::STDOUT> {
  static void log(const std::string& msg);
} __attribute__((aligned(16)));

template <>
struct Logger<OutputType::STDERR> {
  static void log(const std::string& msg);
} __attribute__((aligned(16)));

}  // namespace detail

using StdoutConsole = detail::Logger<detail::OutputType::STDOUT>;
using StderrConsole = detail::Logger<detail::OutputType::STDERR>;

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
  const std::string body = "Do something with dimension\n";
};

using MeasureStdout = Predictor<PredictorType::MEASURE, StdoutConsole>;
using DimensionStdout = Predictor<PredictorType::DIMENSION, StdoutConsole>;
using MeasureStderr = Predictor<PredictorType::MEASURE, StderrConsole>;
using DimensionStderr = Predictor<PredictorType::DIMENSION, StderrConsole>;

}  // namespace experiments
