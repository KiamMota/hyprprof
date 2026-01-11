<<<<<<< HEAD
# How HyprProf Works

HyprProf is a simple tool to **import and export Hyprland configurations** between different systems using a structured payload. It relies on a specific folder layout and a manifest file (`hyprprof.json`) to work correctly.

## Dependencies

Inside the HyprProf folder, the following structure and files are required:

### Manifest File: `hyprprof.json`

This JSON file acts as the main descriptor of your profile. It must include:

```json
{
  "schema": "hyprprof/x.x",
  "hyprprof": {
    "profile_name": "your-profile-name",
    "version": "x.x",
    "dependencies": {}
=======
# Hyprprof

Hyprprof is a profile management system for **Hyprland environments**. It enables exporting, installing, and reproducing complete desktop setups across systems, including configuration files, key bindings, visual theming, desktop behavior, and auxiliary components such as bars and wallpapers.

The objective is **deterministic environment replication**: given a profile, the resulting desktop should be functionally and visually identical.

---

## Core Concept

A Hyprprof profile is defined by a **directory-based contract** composed of:

- A mandatory metadata file: `hyprprof.json`
- A mandatory data directory: `payload/`

Hyprprof performs no inference. Every component must be explicitly declared, either through JSON metadata or through the presence of required filesystem paths.

---

## Directory Structure

```
profile/
├── hyprprof.json
└── payload/
    ├── hyprland/
    │   └── hyprconf
    ├── bg/            (optional)
    └── bar/           (optional, conditional)
```


### payload/

The `payload/` directory contains all files that will be installed or exported.

#### payload/hyprland/ (mandatory)

This directory defines the Hyprland-specific configuration.

- `hyprconf`: the main Hyprland configuration file
- `bg/`: directory containing background images used by the profile

If `hyprland/` is missing, the profile is invalid.

#### payload/bar/ (optional, conditional)

Contains the configuration files for the status bar (e.g. Waybar, Eww, etc).

This directory is **optional**, but **conditionally required**:
- If a bar is declared in `hyprprof.json`, `payload/bar/` must exist
- If `payload/bar/` exists but no bar is declared in JSON, the profile is invalid

This enforces symmetry between metadata and actual payload.

Blind spot: this strict coupling improves consistency but reduces composability. You cannot partially reuse payloads without editing JSON, which may slow iteration.

---

## hyprprof.json

`hyprprof.json` is the authoritative description of the environment. It defines **what the profile is**, **what it expects**, and **which components are active**.

### Example

```json
{
  "schema": "hyprprof/0.1",

  "hyprprof": {
    "profile_name": "my hyprland system",
    "version": "0.2.3"
  },

  "apps": {
    "terminal": {
      "provider": "kitty"
    },
    "browser": "firefox",
    "file_manager": "dolphin",
    "file_picker": "rofi"
  },

  "services": {
    "clipboard": "auto",
    "screen_recorder": "disabled",
    "screenshot": "disabled"
>>>>>>> d718064266a7bb0d0a4f3c32d09365fef8b8c02f
  }
}
```

<<<<<<< HEAD
`schema`: A string indicating the schema version of the HyprProf profile. It must appear at the root of the JSON file, e.g., "hyprprof/1.0".

`hyprprof`: Root object containing the main profile information.

`hyprprof.profile_name` (required): The name of your profile.

`hyprprof.version` (required): The version of your profile.

`dependencies` (required, but can be empty initially): An object reserved for listing external dependencies such as tools, scripts, or sources needed by your setup.

## Payload Folder: payload/

The `payload/` directory must exist inside your HyprProf folder and cannot be empty. 
It contains subfolders representing different components of your Hyprland configuration:

`payload/hyprland/`

Place all .conf files for Hyprland here.
(Backgrounds should be in payload/hyprland/bg/).

`payload/bar/`

Contains all configuration files for your bar setup.
All these subfolders are mandatory if they exist in the payload and must not be empty.

HyprProf works by reading the hyprprof.json manifest and the structured payload folder. It ensures that profiles are portable and reproducible 
across systems, with all necessary configurations and assets in their expected locations. Proper folder structure and required JSON fields are crucial for HyprProf to function correctly.
=======
---

## payload/

The `payload/` directory contains all files that will be installed or exported as part of the profile.

### payload/hyprland/ (mandatory)

Defines the Hyprland-specific configuration.

- `hyprconf`: main Hyprland configuration file
- `bg/`: directory containing background images used by the profile

If this directory is missing, the profile is invalid.

---

### payload/bar/ (optional, conditional)

Contains configuration files for the status bar (e.g. Waybar, Eww).

This directory is **optional**, but **strictly coupled to metadata**:

- If a bar is declared in `hyprprof.json`, `payload/bar/` must exist
- If `payload/bar/` exists but no bar is declared in JSON, the profile is invalid

This enforces symmetry between metadata and payload.

Trade-off: this improves reproducibility and validation, but reduces composability. Partial reuse of payloads requires JSON edits, increasing iteration cost.

---

## hyprprof.json

`hyprprof.json` is the authoritative description of the environment. It defines:

- Profile identity
- Expected applications
- Enabled or disabled services
- Compatibility constraints

### Example

```json
{
  "schema": "hyprprof/0.1",

  "hyprprof": {
    "profile_name": "my hyprland system",
    "version": "0.2.3"
  },

  "apps": {
    "terminal": {
      "provider": "kitty"
    },
    "browser": "firefox",
    "file_manager": "dolphin",
    "file_picker": "rofi"
  },

  "services": {
    "clipboard": "auto",
    "screen_recorder": "disabled",
    "screenshot": "disabled"
  }
}
>>>>>>> d718064266a7bb0d0a4f3c32d09365fef8b8c02f
