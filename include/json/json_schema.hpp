#ifndef JSON_SCHEMAS_HPP
#define JSON_SCHEMAS_HPP

#define HYPRPROF_JSON_SCHEMA                                                                       \
    R"(
{
  "$schema": "http://json-schema.org/draft-07/schema#",
  "type": "object",
  "required": ["hyprprof", "version_constraints"],
  "properties": {
    "hyprprof": {
      "type": "object",
      "required": ["authors", "name", "version", "description"],
      "properties": {
        "authors": {
          "type": "array",
          "items": { "type": "string" }
        },
        "name": { "type": "string" },
        "version": { "type": "string" },
        "description": { "type": "string" }
      }
    },
    "version_constraints": {
      "type": "object",
      "required": ["hyprland", "wayland"],
      "properties": {
        "hyprland": { "type": "string" },
        "wayland": { "type": "string" }
      }
    }
  },
  "additionalProperties": false
}
)"

#endif // JSON_SCHEMAS_HPP
