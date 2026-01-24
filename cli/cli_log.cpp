#include "cli_log.hpp"
#include <iostream>

void cli::err(const std::string &what)
{
  std::cout << "hyprprof cli err: " << what << std::endl;
}

void cli::arg_required(const std::string &cmd_name)
{
  std::cout << "hyprprof cli err: '" << cmd_name << "' requires an other argument." << std::endl;

}
