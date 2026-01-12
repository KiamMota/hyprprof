#include "core/environment.hpp"
#include "infra/sys/cmd.hpp"
#include "infra/sys/pack.hpp"
#include <iostream>
#include <string>

void infra::sys::pack::remove_package(core::Environment& env, const std::string &pack_name)
{
  std::string line_string;
  line_string = "sudo " + env.remove_command() + " " + pack_name ;
  execute_fork(line_string);
}

void infra::sys::pack::install_packages_y(core::Environment& env, const std::list<std::string>& packages)
{
    if (packages.empty())
        return;

    std::string sys = "sudo " + env.install_command();

    for (const auto& pkg : packages) {
        sys += " " + pkg;
    }

    sys += " -y";

    std::cout << "Installing packages: ";
    for (const auto& pkg : packages)
        std::cout << pkg << " ";
    std::cout << "...\n";

    execute_fork(sys); // prints on terminal
}


void infra::sys::pack::install_package_y(core::Environment& env, const std::string& pack_name) {
    std::string line_string;
    line_string = "sudo " + env.install_command() + " " + pack_name + " -y";
    execute_fork(line_string);
}

infra::sys::Result infra::sys::pack::install_package_in_background(core::Environment& env, const std::string &pack_name)
{
  std::string line_string;
  line_string = "sudo " + env.install_command() + " " + pack_name + " -y" ;
  std::cout << "installing dependencies in background..." << std::endl;
  return execute_pipe(line_string);
}
