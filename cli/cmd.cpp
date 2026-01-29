#include "cmd.hpp"
#include <vector>
#include "use_cases/install.hpp"
#include "cli_log.hpp"

void cli::cmd::install(const std::vector<std::string>& args) {
    if (args.empty()) {
        arg_required("install");
        return;
    }

    std::string config_name = args[0];

    // Cria o objeto de instalação
    use_cases::Install inst{config_name};
}

void cli::cmd::use(const std::vector<std::string> &args)
{
  if(args.empty())
  {
    arg_required("use");
    return;
  }

  std::string profile = args[0];
}
