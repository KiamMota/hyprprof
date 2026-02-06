#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#define HELP_MESSAGE R"(
Usage:
  hyprprof [command] [options]
Commands:
  make <name>
    Create a new profile with the specified name.
    Example: hyprprof make default

  install <path/url>
    Install a profile from a local path or remote URL.
    Options: --no-run-scripts
    Examples:
      hyprprof install https://myprofile.com
      hyprprof install ./my_local_profile.hyprprof --no-run-scripts

  use
    Use the current configuration or a specific configuration by name.

  export <name>
    Export the current environment into a .hyprprof file.

  using 
    Display information about the current profile.

  list
    Show all installed profiles.

  remove <name|current>
    Delete a profile from the system.
    Examples:
      hyprprof remove <profile>
      hyprprof remove current

)"


#endif // MESSAGE_HPP
