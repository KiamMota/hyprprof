#include "infra/os/hyprctl.hpp"
#include "infra/os/cmd.hpp"

#define RELOAD_COMMAND "hyprctl reload"

infra::os::Result infra::os::hyprctl::reload()
{
  return execute_pipe(RELOAD_COMMAND);
}
