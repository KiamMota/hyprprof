#include "app/install.hpp"
#include <cstddef>
#include <unistd.h>

void install()
{
  app_service::Install app(getcwd(0, NULL));
}

int main(int argn, char** argv)
{
  install();

}
