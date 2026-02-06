#include "cmd.hpp"
#include <iostream>
#include <list>
#include <vector>
#include "use_cases/install.hpp"
#include "cli_log.hpp"
#include "use_cases/show_things.hpp"
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

void cli::cmd::using_(const std::vector<std::string> &args)
{
  if(use_cases::ShowThings::current_profile().empty())
  {
    std::cout << "no profile setted." << std::endl;
    return;
  }
  std::cout << "current profile: " << use_cases::ShowThings::current_profile() << std::endl; 
 
}

void cli::cmd::list(const std::vector<std::string> &args)
{
    std::list<std::string> prof_list = use_cases::ShowThings::list_profiles();
    std::cout << "---" << std::endl;
    for (const auto& v : prof_list) {
        std::cout << v << std::endl;
    }
}


