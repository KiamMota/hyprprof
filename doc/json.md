# **hyprprof.json**

HyprProf uses a JSON manifest to define, configure, and deploy a Hyprland profile. This file must be present in the profile directory for the engine to recognize and process the profile.

## Manifest Objects

### `hyprprof` (object, required)

* `authors`: string array (optional)

  * Name(s) of the profile authors.
* `name`: string (required)

  * Profile name. Should not contain spaces, commas, accents, or special characters.
* `version`: string (required)

  * Profile version in `a.b.c` format.
* `description`: string (optional)

  * Short description of the profile.

### `version_constraints` (object, optional)

* `hyprland`: string (optional)

  * Specifies the compatible Hyprland version using semver rules (`^0.15.0`).
* `wayland`: string (optional)

  * Specifies the compatible Wayland version (`^1.18.0`).

### `build` (object, optional)

* `install_script`: string

  * Script executed when the profile is installed.
* `uninstall_script`: string

  * Script executed when the profile is removed.
* `other_scripts`: string array

  * Additional scripts to run during installation or configuration.

### `components` (object, optional)

Specifies the core programs of the Hyprland environment:

* `terminal`: string
* `launcher`: string
* `notification`: string
* `bar`: string

### `providers` (object, optional)

Specifies utility programs:

* `wallpaper`: string
* `screenshot`: string
* `clipboard`: string
* `screen_recorder`: string

## Example

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

## Notes

* All scripts referenced in `build` must exist in the profile folder or the designated scripts directory.
* `components` and `providers` allow HyprProf to install and configure the full environment automatically.
* `version_constraints` ensure compatibility and prevent installation on unsupported versions of Hyprland or Wayland.
