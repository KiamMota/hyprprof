#ifndef CLI_COMMANDS_HPP
#define CLI_COMMANDS_HPP

#include "cli11/include/CLI/App.hpp"

namespace cli
{
  class Commands
    {
    private:
      CLI::App cli;
      int argn; char** argv;
      void _AddInstallCmd();
      void _AddExportCmd();
    public:
      Commands(int argn, char** argv);
      int Execute();
  };
}

#endif
