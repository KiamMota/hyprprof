#include "os/hyprctl.hpp"
#include "os/cmd.hpp"

#define RELOAD_COMMAND "hyprctl reload"

os::Result os::hyprctl::reload()
{
  return execute_pipe(RELOAD_COMMAND);
}
