# Hyprprof

Hyprprof is a profile manager for Hyprland, the Wayland compositor. It allows users to define, configure, and deploy a complete Hyprland environment through a structured JSON manifest, making setups modular, repeatable, and portable.

## Features

* **Core Components Configuration**: Configure compositor, terminal, launcher, notification system, and status bar.
* **Providers**: Specify wallpaper managers, screenshot tools, clipboard managers, and screen recorders.
* **Build Scripts**: Automate installation, uninstallation, and other setup scripts.
* **Version Constraints**: Ensure compatibility with specific Hyprland or Wayland versions.
* **Portable & Shareable**: Profiles can be shared or reused across systems without manual reconfiguration.

## Getting Started

1. **One-line installation**:

   You can download and install Hyprprof in a single line using `curl`:

   ```bash
   curl -fsSL https://raw.githubusercontent.com/yourusername/hyprprof/main/install.sh | bash
   ```

   This command downloads the `install.sh` script and executes it directly. After installation, the script cleans up temporary files automatically.

## JSON Manifest Example

```json
{
  "hyprprof": {
    "authors": "Your Name",
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
    "compositor": "hyprland",
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

## License

MIT License

```

