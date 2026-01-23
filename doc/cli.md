# HyprProf CLI Documentation

## Overview

HyprProf is the official CLI client for managing Hyprland profiles. It allows you to create, install, export, and inspect Hyprland environments using a command-line interface. HyprProf is primarily designed as a static library, enabling multiple clients to interact with it via pipes, which opens possibilities for future graphical interfaces.

## Usage

```bash
hyprprof [command] [options]
```

### General Options

* `-h`, `--help`: Display help information.
* `-v`, `--version`: Display the application version.

## Commands

### `make <name>`

Create a new profile with the specified name.

**Example:**

```bash
hyprprof make default
```

### `install <path/url>`

Install a profile from a local path or remote URL. This runs the full execution pipeline, installing dependencies and configuring the environment.

**Options:**

* `--no-run-scripts`: Install the profile without executing scripts. Use with caution, as it may cause inconsistencies.

**Example:**

```bash
hyprprof install https://myprofile.com
hyprprof install ./my_local_profile.hyprprof --no-run-scripts
```

### `export <name>`

Export the current environment into a `.hyprprof` profile file. This scans folders, copies files, and generates a JSON representation.

**Example:**

```bash
hyprprof export my_profile
```

### `info`

Display information about the current profile, such as name, version, and source repository if installed via URL.

**Example:**

```bash
hyprprof info
```

### `uninstall` / `delete`

Delete the currently active profile from the system.

**Example:**

```bash
hyprprof uninstall
```

## Examples

```bash
# Create a new profile named 'default'
hyprprof make default

# Install a profile from a remote URL
hyprprof install https://myprofile.com

# Install a local profile without running scripts
hyprprof install ./my_local_profile.hyprprof --no-run-scripts

# Export the current environment to a file
hyprprof export my_profile

# Show current profile information
hyprprof info

# Delete the current profile
hyprprof uninstall
```

## Notes

* It is recommended to use `sudo` when installing profiles to ensure all dependencies are installed correctly.
* Always review profiles and scripts before installation to avoid potential system inconsistencies.
