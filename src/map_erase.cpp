#include <cstdlib>
#include <iostream>
#include <set>
#include <string>

namespace {
    std::set<std::string> lookup = {"1", "2", "3"};
}

int main() {
    for (auto &item : lookup) {
        lookup.erase(item);
    }

    std::cout << lookup.size() << "\n";
    return EXIT_SUCCESS;
}
