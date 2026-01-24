#include "cmd.hpp"
#include <iostream>
#include <vector>
#include "appservice/install.hpp"
#include "appservice/show_profile.hpp"
#include "cli_log.hpp"

void cli::cmd::install(const std::vector<std::string>& args) {
    if (args.empty()) {
        arg_required("install");
        return;
    }

    std::string config_name = args[0];

    // Cria o objeto de instalação
    app_service::Install inst{config_name};
}

void cli::cmd::use(const std::vector<std::string> &args)
{
  if(args.empty())
  {
    arg_required("use");
    return;
  }

  std::string profile = args[0];
  app_service::ShowProfile show{};
}
