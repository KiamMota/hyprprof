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
  }
}
```

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
