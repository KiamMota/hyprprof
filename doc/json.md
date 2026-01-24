# **hyprprof.json**

The `hyprprof.json` file defines, configures, and allows HyprProf to install and manage a Hyprland profile. It must be present in the profile directory for HyprProf to recognize and process the profile.

---

## Manifest Objects

## `hyprprof` (object, required)

This object defines the main metadata of the profile.

* `authors`: array of strings (optional)

  List of profile authors.
  Each entry must be a simple name composed only of uppercase or lowercase letters (`A–Z`, `a–z`).
  Spaces, accents, numbers, and special characters are not allowed.

* `name`: string (required)

  Profile name.
  This field is used as an internal identifier and must remain simple and predictable.
  Accepted rules:

  * Only uppercase or lowercase letters (`A–Z`, `a–z`) and underscores (`_`)
  * Must start with a letter
  * No spaces, commas, accents, or special characters

  Valid examples:

  * `default`
  * `my_profile`

  Invalid examples:

  * `my profile` (contains spaces)
  * `profile,test` (contains comma)
  * `perfilção` (contains accents)

* `version`: string (required)

  Profile version following the semantic format `a.b.c`, where each segment is a non-negative integer.

  Valid examples:

  * `1.0.0`
  * `0.1.123`

  Invalid examples:

  * `1.0`
  * `v1.0.0`

* `description`: string (optional)

  Free-form textual description of the profile.
  This field accepts any valid string and has no additional restrictions.


  * Short description of the profile.

### `version_constraints` (object, optional)

* `hyprland`: string (optional)

  * Compatible Hyprland version using semver rules (e.g., `^0.15.0`).
* `wayland`: string (optional)

  * Compatible Wayland version (e.g., `^1.18.0`).

### `build` (object, optional)

* `install_script`: string

  * Script executed when the profile is installed.
* `uninstall_script`: string

  * Script executed when the profile is removed.
* `other_scripts`: string array

  * Additional scripts to run during installation or configuration.

### `components` (object, optional)

Specifies the core programs of the Hyprland environment. Possible values include:

* `terminal`: string (e.g., `kitty`, `alacritty`, `gnome-terminal`, `foot`)
* `launcher`: string (e.g., `rofi`, `dmenu`, `wofi`)
* `notification`: string (e.g., `mako`, `dunst`)
* `bar`: string (e.g., `waybar`, `polybar`)
* `compositor`: string (optional, e.g., `hyprland`)
* `browser`: string (optional, e.g., `firefox`, `chromium`, `brave`, `qutebrowser`, `vivaldi`)

### `providers` (object, optional)

Specifies utility programs. Possible values include:

* `wallpaper`: string (e.g., `hyprpaper`, `feh`, `nitrogen`)
* `screenshot`: string (e.g., `grim`, `maim`, `scrot`)
* `clipboard`: string (e.g., `wl-clipboard`, `xclip`, `xsel`)
* `screen_recorder`: string (e.g., `obs`, `wf-recorder`, `peek`)

---

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
    "bar": "waybar",
    "compositor": "hyprland",
    "browser": "firefox"
  },
  "providers": {
    "wallpaper": "hyprpaper",
    "screenshot": "grim",
    "clipboard": "wl-clipboard",
    "screen_recorder": "obs"
  }
}
```
