# Hyprprof Profile Layout

This document describes the correct structure of a Hyprprof profile to ensure functionality and compatibility.

## Directory and File Structure

```
profile_name/
├── hyprprof.json            # Main profile configuration file (mandatory)
├── config/                  # Mandatory folder containing profile-specific configurations
│   ├── waybar/              # Optional folder for Waybar configurations
│   ├── hypr/                # Optional folder for Hyprland configurations
│   └── dotfiles/
├── assets/                  # Optional folder for additional resources (backgrounds, fonts, icons, etc.)
└── README.md                # Optional file for documentation or profile description
```

## Components Description

### hyprprof.json (mandatory)

* Contains the profile's configuration schema.
* Must follow the format described in the [Hyprprof JSON documentation](https://github.com/KiamMota/hyprprof/blob/main/doc/json.md).

### config/ (mandatory)

* Contains all necessary configuration files for the profile.
* Can include subfolders like `waybar/` or `hypr/` for specific application setups.
* Can include `dotconfigs/` for system dotfiles.

### dotconfigs/ (optional)

* Holds dotfiles for applications such as `kitty`, `neovim`, `zsh`, etc.
* Hyprprof will copy these into the user’s system configuration folder when the profile is used.

### assets/ (optional)

* Contains additional resources like backgrounds, fonts, or icons.
* Useful for enhancing the visual appearance of the profile.

### README.md (optional)

* Provides a description of the profile or instructions for use.
* Helps others understand the purpose and setup of the profile.
****
