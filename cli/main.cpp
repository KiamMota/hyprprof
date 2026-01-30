#include <iostream>
#include <string>
#include <vector>
#include "cmd.hpp" 
#include "message.hpp"
#include "dispatcher.hpp"

void register_commands() {
    // registra o comando "install"
    cli::register_command("install",
                          [](const std::vector<std::string>& args) { cli::cmd::install(args); });
    cli::register_command("use", [](const std::vector<std::string>& args) { cli::cmd::use(args);});
    cli::register_command("--update", [](const std::vector<std::string>& args) { cli::cmd::install(args);});

}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        // se não passou nada, mostra help
        std::cout << HELP_MESSAGE << "\n";
        return 0;
    }

    register_commands();

    std::string first_arg = argv[1];

    // flags globais
    if (first_arg == "-h" || first_arg == "--help") {
        std::cout << "hyprprof help\n";
        std::cout << "Available commands:\n";
        for (auto& cmd : cli::list_commands()) {
            std::cout << "  " << cmd << "\n";
        }
        return 0;
    }

    if (first_arg == "-v" || first_arg == "--version") {
        std::cout << "hyprprof version 0.1\n";
        return 0;
    }

    // qualquer outro argumento é tratado como comando
    std::string command = first_arg;
    std::vector<std::string> args;
    for (int i = 2; i < argc; ++i) {
        args.push_back(argv[i]);
    }

    cli::execute_command(command, args);

    return 0;
}
