# Hyprprof Manifest Documentation

This document explains each field in the `Hyprprof` manifest, based on the JSON Schema and validation rules. It serves as a reference for developers and profile creators.

---

## Main Fields

### `hyprprof`

A required object containing general profile information.

* **`authors`**: array of strings.

  * Contains the names of the profile authors.
  * **Rules**:

    * Must have at least one author.
    * Each author cannot be empty.

* **`name`**: string.

  * Profile name.
  * **Rules**:

    * Cannot be empty.
    * Can only contain uppercase and lowercase letters and underscores.

* **`version`**: string.

  * Profile version.
  * **Rules**:

    * Cannot be empty.
    * Must be a numeric version with three parts separated by dots, optionally followed by additional digits (like `1.0.0` or `1.0.0.1`).

* **`description`**: string.

  * Profile description.
  * **Rules**:

    * Can be empty.
    * Cannot exceed 255 characters.

### `version_constraints`

A required object defining minimum versions of dependencies.

* **`hyprland`**: string.

  * Minimum compatible Hyprland version.
  * **Rules**:

    * Cannot be empty.
    * Must be in the format `X.Y.Z` or `^X.Y.Z`.
    * The system version must be equal or higher than the specified version.

* **`wayland`**: string.

  * Minimum compatible Wayland version.
  * **Rules**:

    * Cannot be empty.
    * Must be in the format `X.Y.Z` or `^X.Y.Z`.
    * The system version must be equal or higher than the specified version.

### `dotfiles`

An optional object mapping configuration for applications or utilities.

* Each key inside `dotfiles` can be any name (`kitty`, `nvim`, `zsh`, etc.).
* **Structure of each object**:

  * **`pack`**: string. Name of the package or tool.
  * **`target`**: string. Destination path on the user's system.
  * **`source`**: string. Source path of the dotfile.
* **Rules**:

  * Objects are optional; their absence is allowed.
  * If present, all three fields (`pack`, `target`, `source`) are required.
  * No additional fields are allowed inside each dotfile.

### General Constraints

* No extra fields are allowed outside `hyprprof`, `version_constraints`, and `dotfiles`.
* All internal objects must respect the defined types and required fields.
* Name and version fields follow specific patterns:

  * `name`: only letters and underscores.
  * `version`: three-part numeric version, optionally with extra digits.
  * `hyprland` and `wayland` versions: numeric versions with optional caret (`^`) prefix.
 

# Hyprprof Manifest Example

This is an example of a valid `Hyprprof` manifest, including explanations about `$DOTCONFIG` expansion and dotfile sources.

```json
{
  "hyprprof": {
    "authors": ["Alice", "Bob"],
    "name": "MyProfile_One",
    "version": "1.2.0",
    "description": "This is my Hyprprof profile for testing."
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

## Notes

* `$DOTCONFIG` in the manifest will be expanded by the Hyprprof interpreter to the user's `~/.config` directory. For example, `"target": "$DOTCONFIG/kitty"` becomes `~/.config/kitty`.
* The `source` field in each dotfile object points to a **subdirectory inside `config/dotfiles`** from which the files will be copied. For example, `"source": "kitty"` means files are taken from `config/dotfiles/kitty`.
* Dotfile objects are optional; if present, they must contain `pack`, `target`, and `source`. No additional fields are allowed.
* All other fields follow validation rules:

  * `name`: letters and underscores only.
  * `version`: numeric format `X.Y.Z`.
  * Hyprland and Wayland versions: optional `^` prefix allowed.

