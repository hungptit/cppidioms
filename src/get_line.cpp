
#include <cstdlib>
#include <fstream>
#include <ios>
#include <iostream>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <string>

struct HyperParams {
    explicit HyperParams(const std::string &fname) {
        std::fstream fs;
        fs.open(fname, std::ios::in);
        if (!fs.is_open() || !fs.good()) {
            const std::string errmsg = "Cannot open: " + fname;
            throw std::runtime_error(errmsg);
        }
        std::string line;

        std::getline(fs, line);
        D = std::atof(line.data());

        std::getline(fs, line);
        C = std::atof(line.data());
    }

    double D = 0.0;
    double C = 0.0;
};

std::ostream &operator<<(std::ostream &os, const HyperParams &params) {
    os << "{D = " << params.D << ", "
       << "C = " << params.C << "}\n";
    return os;
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        HyperParams params(argv[1]);
        std::cout << "hyper-parameters: " << params << "\n";
    }
}
