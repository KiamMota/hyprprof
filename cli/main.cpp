#include "infra/version.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    if (argc < 2) {
        std::cout << "No arguments provided. Use -h or --help for usage.\n";
        return 0;
    }

    std::string arg = argv[1];

    if (arg == "-h" || arg == "--help") {
        std::cout << "Usage: mycli [options]\n";
        std::cout << "  -h, --help      Show this help message\n";
        std::cout << "  -v, --version   Show version info\n";
    } 
    else if (arg == "-v" || arg == "--version") {
      std::cout << app::version::VERSION << std::endl;
    } 
    else {
        std::cout << "Unknown option: " << arg << "\n";
        std::cout << "Use -h or --help for usage.\n";
        return 1;
    }

    return 0;
}

