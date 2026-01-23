#include <cstring>
#include <unistd.h>
#include "infra/version.hpp"
#include <iostream>

void help() {
    std::cout << "Hyprprof - CLI Profile Manager for Hyprland\n\n";
    std::cout << "Usage:\n";
    std::cout << "  hyprprof -h, --help           Show this help message\n";
    std::cout << "  hyprprof -v, --version        Show the application version\n\n";

    std::cout << "Commands:\n";
    std::cout << "  make <name>                   Create a new profile with the specified name\n";
    std::cout << "  install <path/url>            Install a profile from a path or URL\n";
    std::cout << "  info                          Show information about the current profile\n";
    std::cout << "  uninstall | delete            Delete the current profile\n\n";

    std::cout << "Examples:\n";
    std::cout << "  hyprprof make default\n";
    std::cout << "  hyprprof install https://myprofile.com\n";
    std::cout << "  hyprprof info\n";
    std::cout << "  hyprprof uninstall\n";
}


int main(int argc, char** argv) {
  
    if(argc == 1)
    {
      help();
      return 0;
    }

    if(argc > 1)
    {
      if(strcmp(argv[1], "-v") == 0 || strcmp(argv[1], "--version") == 0)
      {
        std::cout << app::version::VERSION << "\n";
        return 0;  
      }
      if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
      {
        help();
        return 0;
      } 
    }
    return 0;
}



