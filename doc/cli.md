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

Install a profile from a local path or remote URL. This runs the full execution pipeline, installing dependencies but it doesn't run the environment.

**Options:**

* `--no-run-scripts`: Install the profile without executing scripts. Use with caution, as it may cause inconsistencies.

**Example:**

```bash
hyprprof install https://myprofile.com
hyprprof install ./my_local_profile.hyprprof --no-run-scripts
```

### `use`

The `use` command in Hyprprof allows you to select the Hyperland configuration you want to apply.

It works in two ways:

1. **Use the current configuration installed on the system:**

   ```bash
   hyprprof use
   ```

   This command reads the `~/.hyprprof_current.json` file and applies the configuration currently marked as active.

2. **Use a specific configuration by name:**

   ```bash
   hyprprof use <name>
   ```

   Replace `<name>` with the name of the configuration you want to use. This configuration must be previously saved in `~/.config/hyprprof`.

#### Usage example:

* To continue using the current configuration:

  ```bash
  $ hyprprof use
  Using current configuration: default_profile
  ```

* To switch to a specific profile named `gaming_profile`:

  ```bash
  $ hyprprof use gaming_profile
  Using configuration: gaming_profile
  ```

### `export <name>`

Export the current environment into a `.hyprprof` profile file. This scans folders, copies files, and generates a JSON representation.

**Example:**

```bash
hyprprof export my_profile
```



### `show`

Display information about the current profile, such as name, version, and source repository if installed via URL.

**Example:**

```bash
hyprprof show
```

### `list`

Show all installed profiles.

**Example:**

```bash
hyprprof list
```

### `remove <name|current>`

Delete a profile from the system. You can remove a specific profile by name or the currently active profile using `current`.

**Example:**

```bash
hyprprof remove <profile>
hyprprof remove current
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
hyprprof show

# List all installed profiles
hyprprof list

# Delete a specific profile
hyprprof remove my_profile

# Delete the current profile
hyprprof remove current
```

## Notes

* It is recommended to use `sudo` when installing profiles to ensure all dependencies are installed correctly.
* Always review profiles and scripts before installation to avoid potential system inconsistencies.
