#include "message.hpp"

#include <iostream>
#include <string>

namespace experiments {

message<MessageType::REQUEST>::message(const std::string& str) noexcept
    : msg(str) {}

void message<MessageType::REQUEST>::operator()() { std::cout << msg; }

void message<MessageType::RESPONSE>::operator()() { std::cout << body; }
}  // namespace experiments
