#pragma once

#include <iostream>
#include <string>

namespace experiments {

namespace detail {

enum class OutputType { STDOUT, STDERR };

template <OutputType>
struct Console;

// We can hide the implementation in the library because everything is known
// at the compile time.
template <>
struct Console<OutputType::STDOUT> {
  static void write(const std::string& msg);
};

template <>
struct Console<OutputType::STDERR> {
  static void write(const std::string& msg);
};

}  // namespace detail

using StdoutConsole = detail::Console<detail::OutputType::STDOUT>;
using StderrConsole = detail::Console<detail::OutputType::STDERR>;

enum class MessageType { INVALID, REQUEST, RESPONSE };

template <MessageType, typename Output = StdoutConsole>
struct message;

template <typename Output>
struct message<MessageType::REQUEST, Output> {
  message(const std::string& str) { msg = str; }
  void operator()() { Output::write(msg); }
  std::string msg;
  Output out;
};

template <typename Output>
struct message<MessageType::RESPONSE, Output> {
  void operator()() { Output::write(body); }
  const std::string body = "Response\n";
  Output out;
};

using RequestStdout = message<MessageType::REQUEST, StdoutConsole>;
using ResponseStdout = message<MessageType::RESPONSE, StdoutConsole>;
using RequestStderr = message<MessageType::REQUEST, StderrConsole>;
using ResponseStderr = message<MessageType::RESPONSE, StderrConsole>;

}  // namespace experiments
