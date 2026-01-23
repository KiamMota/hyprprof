# HyprProf

Hyprprof is a profile manager for Hyprland, the Wayland compositor. It allows users to define, configure, and deploy a complete Hyprland environment through a structured JSON manifest, making setups modular, repeatable, and portable.

## Features

* **Core Components Configuration**: Configure compositor, terminal, launcher, notification system, and status bar.
* **Providers**: Specify wallpaper managers, screenshot tools, clipboard managers, and screen recorders.
* **Build Scripts**: Automate installation, uninstallation, and other setup scripts.
* **Version Constraints**: Ensure compatibility with specific Hyprland or Wayland versions.
* **Portable & Shareable**: Profiles can be shared or reused across systems without manual reconfiguration.

## Getting Started

### One-line installation

You can download and install Hyprprof in a single line using `curl`:

```bash
git clone https://github.com/KiamMota/hyprprof.git && cd hyprprof
chmod +x install.sh && ./install.sh
rm -rf ./*
```

This command downloads the `install.sh` script from the official repository and executes it directly. After installation, the script cleans up temporary files automatically.

### Repository

If you want to clone the repository instead:

```bash
git clone https://github.com/KiamMota/hyprprof.git
cd hyprprof
./install.sh
```

## JSON Manifest Example

```json
{
  "hyprprof": {
    "authors": ["Me", "Linus Torvalds"],
    "name": "my_profile",
    "version": "1.0.0",
    "description": "Minimal functional profile for Hyprland"
  },
  "version_constraints": {
    "hyprland": "^0.15.0",
    "wayland": "^1.18.0"
  },
  "build": {
    "install_script": "install.sh",
    "uninstall_script": "uninstall.sh",
    "other_scripts": []
  },
  "components": {
    "terminal": "kitty",
    "launcher": "rofi",
    "notification": "mako",
    "bar": "waybar"
  },
  "providers": {
    "wallpaper": "hyprpaper",
    "screenshot": "grim",
    "clipboard": "wl-clipboard",
    "screen_recorder": "obs"
  }
}
```

## Documentation

For detailed CLI commands and usage, refer to the CLI documentation in [doc/cli](doc/cli.md).

For detailed information about creating and structuring profiles, see the profile documentation in [doc/profile](doc/profile.md).
