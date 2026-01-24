#ifndef CLI_LOG_HPP
#define CLI_LOG_HPP

#include <string>
namespace cli
{
  void err(const std::string& what);
  void arg_required(const std::string& cmd_name);
}

#endif // CLI_LOG_HPP
