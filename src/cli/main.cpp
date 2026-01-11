#include "app/install.hpp"
#include "infra/cmd.hpp"
#include <unistd.h>

void install(const std::string& path)
{
  app_service::Install app(path);
}

int main(int argn, char** argv)
{
  infra::cmd::install_package_in_background("vim");
  infra::cmd::execute_fork("echo 'hello'");
}
