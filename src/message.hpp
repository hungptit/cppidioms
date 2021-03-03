#pragma once

#include <iostream>
#include <string>

namespace experiments {
enum class MessageType { NONE, HELLO, GOODBYE };

template <MessageType type>
struct message;

template <>
struct message<MessageType::HELLO> {
  message(const std::string& str) noexcept;
  void operator()();
  std::string msg;
};

template <>
struct message<MessageType::GOODBYE> {
  void operator()();
  std::string msg;
};

}  // namespace experiments
