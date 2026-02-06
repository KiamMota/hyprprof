# Hyprprof Manifest Explained — Field by Field

This explanation provides deeper insight into each field of the `Hyprprof` manifest, clarifying how the system uses them and why certain rules exist.

---

## `hyprprof`

This object contains the general metadata of a profile. Every Hyprprof profile must have this object.

* **`authors`**: Array of strings.

  * Lists the names of the profile creators or maintainers.
  * **Purpose:** Hyprprof can display author information and track ownership of profiles.
  * **Rules:** Must include at least one author; entries cannot be empty.

* **`name`**: String.

  * Acts as the unique identifier of the profile inside the Hyprprof system.
  * **Purpose:** This name is used to create the profile folder under Hyprprof's path. For instance, a profile named `MyProfile_One` will reside at `~/.config/hyprprof/MyProfile_One/`. Because it is used as a filesystem path, the name must follow restrictions.
  * **Rules:** Cannot be empty; must contain only letters (upper or lowercase) and underscores. This ensures valid directory names and avoids conflicts.

* **`version`**: String.

  * Denotes the version of the profile.
  * **Purpose:** Helps users and Hyprprof track updates, rollback changes, and maintain compatibility.
  * **Rules:** Must follow the `X.Y.Z` format, optionally with extra digits (`1.0.0` or `1.0.0.1`). Cannot be empty.

* **`description`**: String.

  * A human-readable explanation of the profile’s purpose.
  * **Rules:** Optional; can be empty but limited to 255 characters for clarity.

---

## `version_constraints`

Defines minimum versions of dependencies needed for the profile to function properly.

* **`hyprland`**: String.

  * The minimum compatible version of the Hyprland compositor.
  * **Purpose:** Ensures the profile uses features supported by the installed Hyprland version.
  * **Rules:** Cannot be empty; must be formatted `X.Y.Z` or `^X.Y.Z`. The system version must be equal or higher.

* **`wayland`**: String.

  * The minimum compatible version of the Wayland protocol.
  * **Purpose:** Ensures the profile works correctly with Wayland APIs.
  * **Rules:** Cannot be empty; must be formatted `X.Y.Z` or `^X.Y.Z`. The system version must be equal or higher.

---

## `dotfiles`

An optional object mapping configuration for individual applications or utilities.

* Each key represents an application (e.g., `kitty`, `nvim`, `zsh`).
* Each object contains:

  * **`pack`**: Name of the package or application. Used for informational purposes and potential package management.
  * **`target`**: Path on the user’s system where the dotfiles should be applied. `$DOTCONFIG` is replaced with `~/.config`.
  * **`source`**: Relative path inside `config/dotfiles` containing the dotfiles to copy.
* **Rules:** Objects are optional. If present, all three fields (`pack`, `target`, `source`) are required. No extra fields are allowed.
* **Purpose:** Automates deploying user configurations in a consistent and repeatable way.

---

## General Constraints

* The manifest cannot contain extra fields outside of `hyprprof`, `version_constraints`, and `dotfiles`.
* Internal fields must respect types and required properties.
* The `name` field is crucial as it directly determines the profile folder name, so restrictions exist to avoid filesystem conflicts.
* Version fields ensure clear version tracking and compatibility.

---

## Example Explained

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

* `hyprprof.name` → Determines folder path under `~/.config/hyprprof/`.
* `authors` → Tracks profile ownership.
* `version` → Tracks updates and changes.
* `description` → Human-readable explanation.
* `version_constraints` → Ensures the profile only runs if Hyprland/Wayland versions are compatible.
* `dotfiles` → Automates copying user configurations from profile to system.
* `$DOTCONFIG` → Automatically expanded to `~/.config`.

This manifest is usually not written manually by the user; Hyprprof provides a TUI (Text User Interface) that generates and edits this manifest, ensuring validity and correctness.
