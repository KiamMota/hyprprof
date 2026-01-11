#include "infra/cmd/pack.hpp"
#include "domain/environment.hpp"
#include "infra/cmd.hpp"
#include <iostream>
#include <string>

void infra::cmd::pack::remove_package(const std::string &pack_name)
{
  domain::Environment env{};
  std::string line_string;
  line_string = "sudo " + env.remove_command() + " " + pack_name + " -y";
  execute_fork(line_string);
}

void infra::cmd::pack::install_packages_y(const std::list<std::string>& packages)
{
    if (packages.empty())
        return;

    domain::Environment env{};
    std::string cmd = "sudo " + env.install_command();

    // adiciona todos os pacotes à linha de comando
    for (const auto& pkg : packages) {
        cmd += " " + pkg;
    }

    // adiciona -y para não pedir confirmação
    cmd += " -y";

    std::cout << "Installing packages: ";
    for (const auto& pkg : packages)
        std::cout << pkg << " ";
    std::cout << "...\n";

    execute_fork(cmd); // imprime tudo no terminal em tempo real
}


void infra::cmd::pack::install_package_y(const std::string& pack_name) {
    domain::Environment env{};
    std::string line_string;
    line_string = "sudo " + env.install_command() + " " + pack_name + " -y";
    execute_fork(line_string);
}

infra::cmd::Result infra::cmd::pack::install_package_in_background(const std::string &pack_name)
{
  domain::Environment env{};
  std::string line_string;
  line_string = "sudo " + env.install_command() + " " + pack_name + " -y" ;
  std::cout << "installing dependencies in background..." << std::endl;
  return execute_pipe(line_string);
}
