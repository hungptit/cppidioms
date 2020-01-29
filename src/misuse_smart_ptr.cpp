#include <iostream>
#include <map>
#include <unordered_map>
#include <memory>
#include <set>

struct Object {
    Object(const std::string &val) : data(val) {}
    ~Object() { std::cout << "Destructor: " << data << "\n"; }
    void print(const std::string &msg) const { std::cout << msg << ":" << data << "\n"; }
    std::string data;
    static Object* create(const std::string &data) {
        return new Object(data);
    }
};

void shared_ptr_case() {
    using Map = std::map<int, std::shared_ptr<Object>>;
    auto obj2 = Object::create("obj2");
    Map map{{0, std::make_shared<Object>("First item")}};
    map.insert(std::make_pair(0, obj2));
    obj2->print("Should segv");
}

int main() {
    shared_ptr_case();
}
