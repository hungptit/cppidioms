#include <clara.hpp> // Only has two header files
#include <iostream>

struct Params {
    int age = -1;
    double salary = 0;
    bool manager = false;
    std::string full_name = "John Doe";
};

std::ostream &operator<<(std::ostream &os, const Params &params) {
    os << "Full name: " << params.full_name << "\n";
    os << "Manager:   " << (params.manager ? "Yes" : "No") << "\n";
    os << "Age:       " << params.age << "\n";
    os << "Salary:    " << params.salary << "\n";
    return os;
}

int main(int argc, char *argv[]) {
    Params params;
    bool show_help_message = false;
    bool show_version = false;

    auto cli = clara::Help(show_help_message) |
               clara::Opt(show_version)["-v"]["--version"]("Show the version of this example") |
               clara::Opt(params.age, "age")["-a"]["--age"]("Employee's age.") |
               clara::Opt(params.salary, "salary")["-s"]["--salary"]("Employee's salary.") |
               clara::Opt(params.manager)["-m"]["--manager"]("Is manager?") |
               clara::Arg(params.full_name, "Full name")("Employee full name.");
    auto result = cli.parse({argc, argv});
    if (!result) {
        std::cerr << "Error in command line: " << result.errorMessage() << std::endl;
        return EXIT_FAILURE;
    }

    if (show_help_message || !result) {
        std::cout << cli << "\n";
        return EXIT_FAILURE;
    }

    if (show_version) {
        std::cout << "Version: 1.92\n";
        return EXIT_SUCCESS;
    }

    std::cout << params;
    return EXIT_SUCCESS;
}
