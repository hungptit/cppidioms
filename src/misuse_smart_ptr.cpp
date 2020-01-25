#include <iostream>
#include <map>
#include <memory>
#include <set>

struct Object {
    Object(const std::string &val) : data(val) {}
    ~Object() { std::cout << "Destructor: " << data << "\n"; }
    void print(const std::string &msg) const { std::cout << msg << ":" << data << "\n"; }
    std::string data;
};

int main() {
    Object obj1("World");
    obj1.print("Hello");
    Object *obj2 = new Object("obj2");

    {
        std::map<int, std::unique_ptr<Object>> map;
        map.insert(std::make_pair(0, obj2));
    }
    obj2->print("Should segv");
}
