#include "core/install/json_manifest_validator.hpp"
#include "infra/json.hpp"
#include "infra/log.hpp"

#include <rapidjson/error/en.h>
#include <stdexcept>
#include <string>
#include <unistd.h>

core::install::JsonManifestValidator::JsonManifestValidator() {
    _json_schema = R"(
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
        "authors": { "type": "string" },
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
)";
}

void core::install::JsonManifestValidator::Parse(const std::string& json_str)
{
  if(json_str.empty())
    throw std::runtime_error("empty JSON!");
  
  if(infra::json::validate_schema(json_str, _json_schema))
  {
    infra::hypr_log::log("validated json!");
    return;
  }
  infra::hypr_log::err("invalid json!");
}
