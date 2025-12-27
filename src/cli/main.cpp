#include "cli/cli_commands.hpp"
#include <iostream>

int main(int argn, char** argv)
{
  cli::Commands cmd{argn, argv};
  cmd.Execute();
}
