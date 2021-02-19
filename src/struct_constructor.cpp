#include <iomanip>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

namespace {

struct Address {
  int zipcode = 1111;
  std::string company = "Home";
};

struct Contacts {
  std::string description = "My contact";
  std::vector<Address> addresses;
};

std::ostream& operator<<(std::ostream& os, const Address& addr) {
  os << "{" << std::quoted("zipcode") << ":" << addr.zipcode << ","
     << std::quoted("company") << ":" << std::quoted(addr.company) << "}";
  return os;
}

std::ostream& operator<<(std::ostream& os, const Contacts& list) {
  os << "{" << std::quoted("description") << ":"
     << std::quoted(list.description) << "," << std::quoted("addresses")
     << ":[";
  int counter = 0;
  for (const auto& item : list.addresses) {
    if (counter > 0) {
      os << ",";
    }
    os << item;
    ++counter;
  }
  os << "]}";
  return os;
}
}  // namespace

int main() {
  Contacts my_contacts = {"Test", {{0, "A"}, {1, "B"}}};
  std::cout << my_contacts << "\n";
}
