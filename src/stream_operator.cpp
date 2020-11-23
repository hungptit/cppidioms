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
  os << "{";
  int count = 0;
  for (auto it = data.cbegin(); it != data.cend(); ++it) {
    os << (count++ != 0 ? ",{" : "{") << std::quoted(it->first) << ","
       << it->second << "}";
  }
  os << "}";
  return os;
}

template <>
ostream& operator<<(ostream& os,
                    const std::map<std::string, std::string>& data) {
  os << "{";
  int count = 0;
  for (auto it = data.cbegin(); it != data.cend(); ++it) {
    os << (count++ != 0 ? ",{" : "{") << std::quoted(it->first) << ","
       << std::quoted(it->second) << "}";
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

  std::map<std::string, std::string> smap_empty{};
  std::cout << smap_empty << "\n";

  std::map<std::string, std::string> smap_one{{"a", "1"}};
  std::cout << smap_one << "\n";

  return EXIT_SUCCESS;
}
