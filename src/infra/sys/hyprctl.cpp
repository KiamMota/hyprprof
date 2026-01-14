#include "infra/sys/hyprctl.hpp"
#include "infra/sys/cmd.hpp"

#define RELOAD_COMMAND "hyprctl reload"

infra::sys::Result infra::sys::hyprctl::reload()
{
  return execute_pipe(RELOAD_COMMAND);
}
