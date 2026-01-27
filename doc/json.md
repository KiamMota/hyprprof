# **hyprprof.json**

The `hyprprof.json` file defines, configures, and allows HyprProf to install and manage a Hyprland profile. It must be present in the profile directory for HyprProf to recognize and process the profile.

The JSON manifest follows this schema:

``` json
{
  "$schema": "http://json-schema.org/draft-07/schema#",
  "title": "Hyprland Profile Schema",
  "type": "object",
  "required": ["hyprprof", "components", "providers"],
  "properties": {
    "hyprprof": {
      "type": "object",
      "required": ["authors", "name", "version"],
      "properties": {
        "authors": {
          "type": "array",
          "minItems": 1,
          "items": { "type": "string" }
        },
        "name": { "type": "string" },
        "version": { "type": "string", "pattern": "^\\d+\\.\\d+\\.\\d+$" },
        "description": { "type": "string" }
      }
    },
    "version_constraints": {
      "type": "object",
      "properties": {
        "hyprland": { "type": "string", "pattern": "^\\^?\\d+\\.\\d+\\.\\d+$" },
        "wayland": { "type": "string", "pattern": "^\\^?\\d+\\.\\d+\\.\\d+$" }
      }
    },
    "build": {
      "type": "object",
      "properties": {
        "install_script": { "type": "string" },
        "uninstall_script": { "type": "string" },
        "other_scripts": { 
          "type": "array",
          "items": { "type": "string" }
        }
      }
    },
    "components": {
      "type": "object",
      "required": ["terminal", "launcher", "notification"],
      "properties": {
        "compositor": { "type": "string" },
        "terminal": { "type": "string" },
        "launcher": { "type": "string" },
        "notification": { "type": "string" },
        "bar": { "type": "string" },
        "browser": { "type": "string" }
      }
    },
    "providers": {
      "type": "object",
      "required": ["wallpaper", "screenshot", "clipboard", "screen_recorder"],
      "properties": {
        "wallpaper": { "type": "string" },
        "screenshot": { "type": "string" },
        "clipboard": { "type": "string" },
        "screen_recorder": { "type": "string" }
      }
    }
  },
  "additionalProperties": false
}
```

---

## Manifest Objects

## `hyprprof` (object, required)

This object defines the main metadata of the profile.

* `authors`: array of strings (optional)

  List of profile authors.

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

### `version_constraints` (object, required)

This object defines compatibility constraints for external dependencies using semantic versioning rules.

* `hyprland`: string (optional)

  Compatible Hyprland version.
  The value must follow a semantic version format `a.b.c` and may optionally be prefixed with `^`, which indicates "greater than or equal to" the specified version.

  Accepted rules:

  * Optional `^` prefix to indicate a minimum compatible version
  * Three numeric components separated by dots
  * Each component must be a non-negative integer

  Valid examples:

  * `^0.15.0`
  * `1.0.0`

  Invalid examples:

  * `>=0.15.0`
  * `0.15`
  * `v0.15.0`

* `wayland`: string (optional)

  Compatible Wayland version.
  Follows the same semantic version rules as `hyprland`.

  Accepted rules:

  * Optional `^` prefix to indicate a minimum compatible version
  * Three numeric components separated by dots

  Valid examples:

  * `^1.18.0`
  * `1.18.0`

  Invalid examples:

  * `^1.18`
  * `1.18`
  * `~1.18.0`


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
