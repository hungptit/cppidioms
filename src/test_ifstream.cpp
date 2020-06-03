#include <fstream>
#include <iostream>
#include <string>
#include <utility>

int main() {
    std::string   file_name = "example.txt";
    std::ifstream in(file_name);
    if (in.is_open() && in.good()) {
        std::cout << "OK\n";
    } else {
        std::cout << "Cannot open file\n";
    }

    {
        std::string outfile("/root/we_cannot_open_this_file");
        std::ofstream out(outfile, std::ofstream::trunc);
        out.exceptions(std::ofstream::failbit | std::ofstream::badbit);
        out << "1234\n";
    }
}
