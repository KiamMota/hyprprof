#include "dispatcher.hpp"
#include <iostream>
#include <unordered_map>

namespace cli {

    static std::unordered_map<std::string, CommandCallback> command_map;

    void register_command(const std::string& name, CommandCallback callback) {
        command_map[name] = std::move(callback);
    }

    void execute_command(const std::string& name, const std::vector<std::string>& args) {
        auto it = command_map.find(name);
        if (it != command_map.end()) {
            // chama o callback com os argumentos
            it->second(args);
        } else {
            std::cerr << "Unknown command: " << name << "\n";
        }
    }

    std::vector<std::string> list_commands() {
        std::vector<std::string> commands;
        for (const auto& [name, _] : command_map) {
            commands.push_back(name);
        }
        return commands;
    }

} 

