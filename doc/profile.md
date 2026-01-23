# HyprProf Profile Pipeline

This document explains the full pipeline of how HyprProf handles profiles in Hyprland.

## Overview

HyprProf manages profiles by storing them in `~/.config/hyprprof/`. Each profile must contain a `hyprprof.json` file. This JSON file is essential; without it, HyprProf will not recognize the profile.

The pipeline ensures that profiles are installed, tracked, and activated safely and consistently.

## First Installation Pipeline

When you install a profile for the first time using `hyprprof install <profile>`:

1. **Create main config directory**

   * HyprProf checks if `~/.config/hyprprof/` exists.
   * If it does not exist, it creates this directory to store all profiles.

2. **Create profile folder**

   * A subfolder is created inside `~/.config/hyprprof/` using the profile's name.
   * This folder will contain all files related to that specific profile.

3. **Copy profile JSON and payload**

   * The `hyprprof.json` of the profile is copied into the folder.
   * Any additional files or scripts (payload) included with the profile are also copied.

4. **Install components and providers**

   * HyprProf reads the JSON to identify components (terminal, bar, launcher, notification, etc.) and providers (wallpaper, screenshot, clipboard, screen recorder).
   * Each component and provider is installed and configured automatically.

5. **Run installation scripts**

   * If the profile JSON specifies an installation or configuration script (`install.sh` or others), HyprProf executes these scripts.
   * HyprProf supports **native shell scripts**.

6. **Create current profile reference**

   * After installation, HyprProf generates `~/.hyprprof_current.json` to track the active profile.

```json
{
  "current": "~/.config/hyprprof/<active_profile>",
  "others": {}
}
```

* `current` points to the active profile folder.
* `others` can list additional installed profiles.

## Switching Profiles

Using `hyprprof use <other_profile>`:

* HyprProf updates `~/.hyprprof_current.json` to point to the new profile.
* The environment is applied immediately using the scripts already present in the profile folder.
* No reinstallation is needed; the profile is activated directly.

## Important Notes

* **Mandatory `hyprprof.json`**: Each profile must include this JSON. Without it, the profile cannot be found or used.
* **Scripts support**: Any shell scripts included in the profile will be executed automatically by HyprProf for installation and configuration.
* **Isolated profiles**: Each profile resides in its own folder, allowing safe switching and easy management.
* **Reproducibility**: The pipeline ensures that installing or switching profiles does not overwrite other configurations outside the profile folder.

This pipeline allows HyprProf to manage Hyprland profiles efficiently, enabling quick installation, activation, and switching while keeping configurations organized and reproducible.
