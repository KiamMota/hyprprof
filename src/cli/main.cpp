#include "app/install.hpp"
#include "infra/sys/env.hpp"
#include <unistd.h>

int main(int argn, char** argv)
{
  infra::sys::detect_distro_str();
}
