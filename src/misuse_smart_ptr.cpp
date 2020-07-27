#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <unordered_map>

struct Object {
  ~Object() { std::cout << "Destructor: " << data << "\n"; }

  Object(const std::string& data) : data(data) {
    std::cout << "Constructor: " << data << "\n";
  }

  Object(Object&& obj) {
    data = std::move(obj.data);
    std::cout << "Move constructor: " << data << "\n";
  }

  Object(const Object& obj) {
    data = obj.data;
    std::cout << "Copy constructor: " << data << "\n";
  }

  Object& operator=(const Object& obj) {
    data = obj.data;
    std::cout << "Copy assignment constructor: " << data << "\n";
    return *this;
  }

  Object& operator=(Object&& obj) {
    data = std::move(obj.data);
    std::cout << "Copy assignment constructor: " << data << "\n";
    return *this;
  }

  void print(const std::string&) {}

  std::string data;
  static Object* create(const std::string& data) { return new Object(data); }
};

void shared_ptr_case() {
  using Map = std::map<int, std::shared_ptr<Object>>;
  auto obj2 = Object::create("obj2");
  Map map{{0, std::make_shared<Object>("First item")}};
  map.insert(std::make_pair(0, obj2));
  obj2->print("Should segv");
}

int main() { shared_ptr_case(); }
