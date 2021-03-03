#pragma once

#include <iostream>
#include <string>

namespace experiments {
enum class MessageType { INVALID, REQUEST, RESPONSE };

template <MessageType type>
struct message;

template <>
struct message<MessageType::REQUEST> {
  message(const std::string& str) noexcept;
  void operator()();
  std::string msg;
};

template <>
struct message<MessageType::RESPONSE> {
  void operator()();
  std::string body = "Response\n";
};

using Request = message<MessageType::REQUEST>;
using Response = message<MessageType::RESPONSE>;

}  // namespace experiments
