#include "cli/cli_commands.hpp"

cli::Commands::Commands(int argn, char** argv) : cli("hyprprof cli", "hyprprof")
{ 
  _AddInstallCmd();

}

int cli::Commands::Execute()
{
  CLI11_PARSE(cli, argn, argv);
}

void cli::Commands::_AddInstallCmd()
{
  auto cmd = cli.add_subcommand("install", "install an profile in hyprland");
  std::string profile_name;
  cmd->add_option("profile_name", profile_name, "name of the profile")->required(); 



}

