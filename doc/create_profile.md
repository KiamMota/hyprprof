# HyprProf Profile Layout — Beginner-Friendly Guide

This guide explains the structure of a HyprProf profile in a simple way, making it easier to create, use, and share Hyprland setups.


## What is a HyprProf Profile?

A **profile** in HyprProf is a packaged configuration of your Hyprland environment. It contains all the files and settings needed to quickly apply a consistent setup across systems. Think of it as a blueprint that tells HyprProf what to configure, where, and how.

Each profile is structured so that the program can read it automatically, apply dotfiles, Hypr configurations, and optional resources like wallpapers or fonts.


## Profile Directory Structure

Every profile should follow this layout:

```
profile_name/              # Root folder named after your profile
├── hyprprof.json          # Main configuration file (mandatory)
├── config/                # Folder for application-specific configs (mandatory)
│   ├── hypr/              # Hyprland configs (optional)
│   ├── waybar/            # Waybar configs (optional)
│   └── dotconfigs/        # Additional dotfiles (optional)
├── assets/                # Extra resources like fonts, icons, wallpapers (optional)
│   ├── bgs/
│   ├── fonts/
│   ├── icons/
└── README.md              # Profile description or instructions (optional)
```

This structure allows HyprProf to know exactly where to look for each configuration type.


## File and Folder Details

### `hyprprof.json` (mandatory)

* Contains metadata about the profile: name, authors, description, version, and constraints for Hyprland or Wayland.
* Must follow HyprProf's JSON schema to work correctly.
* Example fields:

  * `hyprprof.name`
  * `hyprprof.version`
  * `hyprprof.authors`
  * `dotfiles` and `version_constraints`

### `config/` (mandatory)

* Holds the configuration files that HyprProf will deploy.
* Can have subfolders for specific applications:

  * `hypr/` — Hyprland configuration files
  * `waybar/` — Waybar status bar configuration
  * `dotconfigs/` — Other application dotfiles like terminal, editor, or shell

### `dotconfigs/` (optional)

* Contains dotfiles for user applications.
* HyprProf will copy them into the proper system folders when the profile is applied.
* Examples include:

  * `kitty` terminal configs
  * `neovim` or `vim` configs
  * `zsh` or `bash` shell configs

### `assets/` (optional)

* Store extra resources here like:

  * Wallpapers
  * Fonts
  * Icons
* These can enhance the appearance of your environment but are not required for functionality.

### `README.md` (optional)

* Provides a human-readable explanation of the profile.
* Can include instructions, purpose, or notes for sharing with others.

---

By following this structure, anyone can create a profile that HyprProf understands, making it easier to manage and distribute your Hyprland setups consistently.
