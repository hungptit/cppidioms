#include <iostream>
#include <map>
#include <memory>
#include <set>

struct Object {
    ~Object() { std::cout << "Destructor: " << data << "\n"; }

    Object(const std::string &data) : data(data) { std::cout << "Constructor: " << data << "\n"; }

    Object(Object &&obj) {
        data = std::move(obj.data);
        std::cout << "Move constructor: " << data << "\n";
    }

    Object(const Object &obj) {
        data = obj.data;
        std::cout << "Copy constructor: " << data << "\n";
    }

    Object& operator=(const Object &obj) {
        data = obj.data;
        std::cout << "Copy assignment constructor: " << data << "\n";
        return *this;
    }

    Object& operator=(Object &&obj) {
        data = std::move(obj.data);
        std::cout << "Copy assignment constructor: " << data << "\n";
        return *this;
    }

    std::string data;
};

int main() {
    Object obj1("A");
    Object obj2("B");
    Object obj3("C");
    Object obj4("D");

    std::map<int, Object> map;
    map.emplace(0, obj1);

    // // This call does not make any copy
    // map.emplace(0, obj2);

    // // This call does make a copy
    // map.insert(std::make_pair(0, obj3));

    // // This call does make a copy
    // map[0] = obj4;
}
