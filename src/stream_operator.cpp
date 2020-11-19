#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <map>
#include <ostream>
#include <sstream>

namespace std {

template <typename T>
ostream& operator<<(ostream& os, const std::pair<std::string, T>& item) {
  return os << "{" << std::quoted(item.first) << "," << item.second << "}";
}

template <typename Value>
ostream& operator<<(ostream& os, const std::map<std::string, Value>& data) {
  const size_t len = data.size();
  if (len == 0U) {
    os << "{}";
    return os;
  }

  os << "{";
  auto it = data.cbegin();
  os << "{" << std::quoted(it->first) << "," << it->second << "}";
  ++it;

  for (; it != data.cend(); ++it) {
    os << ",{" << std::quoted(it->first) << "," << it->second << "}";
  }
  os << "}";
  return os;
}

template <>
ostream& operator<<(ostream& os,
                    const std::map<std::string, std::string>& data) {
  const size_t len = data.size();
  if (len == 0U) {
    os << "{}";
    return os;
  }

  os << "{";
  auto it = data.cbegin();
  os << "{" << std::quoted(it->first) << "," << std::quoted(it->second) << "}";
  ++it;

  for (; it != data.cend(); ++it) {
    os << ",{" << std::quoted(it->first) << "," << std::quoted(it->second)
       << "}";
  }
  os << "}";
  return os;
}

}  // namespace std

int main() {
  std::pair<std::string, int> item{"a", 1};
  std::cout << item << "\n";

  std::map<std::string, int> intmap{{"a", 1}, {"b", 2}};
  std::cout << intmap << "\n";

  std::map<std::string, std::string> smap{{"a", "1"}, {"b", "2"}};
  std::cout << smap << "\n";

  return EXIT_SUCCESS;
}
