#include "infra/fs/dir.hpp"
#include <unistd.h>

int main(int argn, char** argv)
{
  infra::fs::dir::make_bak("test");
}
