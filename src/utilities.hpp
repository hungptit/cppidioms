#include <cstdint>
#include <iomanip>
#include <map>
#include <ostream>
#include <queue>
#include <type_traits>
#include <utility>
#include <vector>

namespace std {

template <typename K, typename V>
ostream& operator<<(ostream& os, const std::pair<K, V>& item) {
  os << "{";
  if (std::is_same<K, std::string>::value) {
    // os << std::quoted(item.first);
  } else {
    os << item.first;
  }
  os << ",";
  if (std::is_same<V, std::string>::value) {
    os << std::quoted(item.second);
  } else {
    os << item.first;
  }
  os << "}";
  return os;
}

template <typename T>
ostream& operator<<(ostream& os, const std::vector<T>& data) {
  os << "[";
  uint32_t count = 0;
  for (const auto& item : data) {
    if (count++ > 0) os << ",";
    os << item;
  }
  os << "]";
  return os;
}

template <typename K, typename V>
ostream& operator<<(ostream& os, const std::map<K, V>& data) {
  os << "[";
  uint32_t count = 0;
  for (const auto& item : data) {
    if (count++ > 0) os << ",";
    os << item;
  }
  os << "]";
  return os;
}

}  // namespace std
