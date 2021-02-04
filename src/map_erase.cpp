#include <cstdlib>
#include <set>
#include <string>

namespace {
    std::set<std::string> lookup = {"1", "2", "3"};
}

int main() {
    auto &lk = lookup;
    lk.erase("4");
    return EXIT_SUCCESS;
}
