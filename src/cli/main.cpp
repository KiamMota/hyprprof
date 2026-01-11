#include "app/install.hpp"
#include "infra/cmd/pack.hpp"
#include <unistd.h>

void install(const std::string& path)
{
  app_service::Install app(path);
}

int main(int argn, char** argv)
{
  infra::cmd::pack::remove_package("vim");

}
