# HyprProf Manifest Guide — Introductory Version

This document explains the HyprProf manifest, which is the core of how profiles work. The manifest is essentially a map that tells HyprProf everything it needs to know about a profile — what it contains, where files live, and which versions it supports.

Most users will **not edit this file manually**. Instead, HyprProf provides a TUI (Text User Interface) that generates the manifest for you, ensuring all fields are correct and consistent.

---

## What is the Manifest?

A manifest is a **JSON file called `hyprprof.json`** located in the root folder of a profile. It contains:

* Profile metadata (name, authors, description, version)
* System version constraints (Hyprland and Wayland)
* Dotfile and application configuration mappings

It is the single source of truth for HyprProf to deploy, validate, and manage profiles.

## Main Sections

### 1. `hyprprof`

Contains **general information about the profile**.

* **`name`** — Profile identifier. Used to distinguish profiles. Must contain only letters and underscores.
* **`version`** — Profile version. Follows a numeric pattern like `1.0.0`. Helps track updates.
* **`authors`** — Array of strings listing who created or maintains the profile.
* **`description`** — Text explaining what the profile is for. Optional but recommended.

This section allows HyprProf to **display meaningful info** about the profile in the TUI or CLI.

### 2. `version_constraints`

Defines **minimum system requirements** for the profile.

* **`hyprland`** — Minimum compatible Hyprland version. Can use `^` to indicate compatible range.
* **`wayland`** — Minimum compatible Wayland version. Same format.

HyprProf reads this section to **ensure the profile won’t break the system** when applied.

### 3. `dotfiles`

Optional section that lists **application-specific configurations** that will be copied into the user system.

Each dotfile object has:

* **`pack`** — The package or tool name (like `kitty`, `neovim`).
* **`target`** — Path on the system where the files should be placed. `$DOTCONFIG` will be automatically expanded to `~/.config`.
* **`source`** — Subfolder inside the profile (`config/dotfiles/<source>`) containing the files to copy.

HyprProf will iterate over this section and copy files, installing required packages if necessary.

### How the Manifest Works in Practice

1. HyprProf reads `hyprprof.json`.
2. Validates the profile metadata and version constraints.
3. Checks which dotfiles exist.
4. Applies configuration files to the correct system locations.
5. Manages backups automatically.

Because the manifest defines **all the relationships and paths**, HyprProf can safely automate profile application, updates, and sharing.

## Example Manifest

```json
{
  "hyprprof": {
    "authors": ["Alice", "Bob"],
    "name": "MyProfile_One",
    "version": "1.2.0",
    "description": "Example HyprProf profile."
  },
  "version_constraints": {
    "hyprland": "^0.23.5",
    "wayland": "^1.20.5"
  },
  "dotfiles": {
    "kitty": {
      "pack": "kitty",
      "target": "$DOTCONFIG/kitty",
      "source": "kitty"
    },
    "nvim": {
      "pack": "neovim",
      "target": "$DOTCONFIG/nvim",
      "source": "nvim"
    }
  }
}
```

**Notes:**

* `$DOTCONFIG` will automatically point to `~/.config`.
* `source` paths are relative to `config/dotfiles/` inside the profile.
* Dotfile objects are optional, but if present, they **must have all three fields** (`pack`, `target`, `source`).
* The manifest allows HyprProf to **understand the profile’s structure without asking the user**.

---

### Takeaways

* The manifest is **the heart of every HyprProf profile**.
* Users usually **don’t write it manually**; the TUI handles creation.
* Every field exists so that HyprProf can **reliably apply, share, and manage profiles**.
* Understanding it helps you **debug, extend, or inspect profiles**, but rarely requires manual editing.
