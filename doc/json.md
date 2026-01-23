# **hyprprof.json**

The `hyprprof.json` file defines, configures, and allows HyprProf to install and manage a Hyprland profile. It must be present in the profile directory for HyprProf to recognize and process the profile.

---

## Manifest Objects

### `hyprprof` (object, required)

* `authors`: string array (optional)

  * List of profile authors.
* `name`: string (required)

  * Profile name. Should be simple: no spaces, commas, accents, or special characters.
* `version`: string (required)

  * Profile version in `a.b.c` format.
* `description`: string (optional)

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
