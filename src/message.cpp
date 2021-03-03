#include "message.hpp"

#include <iostream>
#include <string>

namespace experiments {

message<MessageType::HELLO>::message(const std::string& str) noexcept
    : msg(str) {}

void message<MessageType::HELLO>::operator()() { std::cout << msg; }

void message<MessageType::GOODBYE>::operator()() { std::cout << msg; }
}  // namespace experiments
