#include "cmd.hpp"
#include <vector>
#include "use_cases/install.hpp"
#include "cli_log.hpp"
#include "use_cases/use.hpp"

void cli::cmd::install(const std::vector<std::string>& args) {
    if (args.empty()) {
        arg_required("install");
        return;
    }

    std::string config_name = args[0];
    bool overwrite_flag = args.size() > 1 && args[1] == "--overwrite";

    // Cria o objeto de instalação
    use_cases::Install inst{config_name, overwrite_flag};
}


void cli::cmd::use(const std::vector<std::string> &args)
{
  if(args.empty())
  {
    arg_required("use");
    return;
  }

  std::string profile = args[0];

  use_cases::Use use{profile};
}

