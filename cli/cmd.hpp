#ifndef CMD_INSTALL_HPP
#define CMD_INSTALL_HPP

#include <string>
#include <vector>
namespace cli {

namespace cmd {
void install(const std::vector<std::string>& args);
void use(const std::vector<std::string>& args);
void update(const std::vector<std::string>& args);
} // namespace cmd
} // namespace cli

#endif // CMD_INSTALL_HPP
