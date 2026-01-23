#ifndef JSON_SCHEMAS_HPP
#define JSON_SCHEMAS_HPP

#define HYPRPROF_JSON_SCHEMA                                                                       \
    R"(
{
  "$schema": "http://json-schema.org/draft-07/schema#",
  "title": "Hyprland Profile Schema",
  "type": "object",
  "required": ["hyprprof", "version_constraints", "build", "components", "providers"],
  "properties": {
    "hyprprof": {
  "type": "object",
  "required": ["authors", "name", "version", "description"],
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
      "required": ["hyprland", "wayland"],
      "properties": {
        "hyprland": { "type": "string", "pattern": "^\\^?\\d+\\.\\d+\\.\\d+$" },
        "wayland": { "type": "string", "pattern": "^\\^?\\d+\\.\\d+\\.\\d+$" }
      }
    },
    "build": {
      "type": "object",
      "required": ["install_script", "uninstall_script", "other_scripts"],
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
      "required": ["compositor", "terminal", "launcher", "notification", "bar"],
      "properties": {
        "compositor": { "type": "string" },
        "terminal": { "type": "string" },
        "launcher": { "type": "string" },
        "notification": { "type": "string" },
        "bar": { "type": "string" }
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
)"

#endif // JSON_SCHEMAS_HPP
