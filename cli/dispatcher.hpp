#ifndef DISPATCHER_HPP
#define DISPATCHER_HPP

#include <string>
#include <vector>
#include <functional>

namespace cli {

    using CommandCallback = std::function<void(const std::vector<std::string>&)>;

    void register_command(const std::string& name, CommandCallback callback);

    void execute_command(const std::string& name, const std::vector<std::string>& args);

    std::vector<std::string> list_commands();

} 

#endif // DISPATCHER_HPP

