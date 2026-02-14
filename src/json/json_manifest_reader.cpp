// JSONManifestReader is responsible for reading and parsing a JSON manifest
// representing a Hyprprof profile. It validates the JSON against a predefined
// schema and provides access to the profile metadata and associated dotfiles.

#include "json/json_manifest_reader.hpp"
#include "dotfile.hpp"
#include "fs/dotconfig.hpp"
#include "profile/profile_model.hpp"
#include "json/json_schema.hpp"
#include "json/json_schema_validator.hpp"
#include <list>
#include <string>

namespace json {

// Constructor for JSONManifestReader
// Initializes the reader with the predefined Hyprprof JSON schema.
JSONManifestReader::JSONManifestReader() { _json_schema = HYPRPROF_JSON_SCHEMA; }

// Parses and validates a JSON string.
// Throws runtime_error if parsing fails or if the JSON does not conform to the schema.
void JSONManifestReader::run(const std::string& json_str) {
    _json_str = json_str;

    // Parse the JSON string into a RapidJSON document
    _document.Parse(_json_str.c_str());

    // Check for parse errors
    if (_document.HasParseError()) {
        throw std::runtime_error("JSON parse error in profile manifest.");
    }

    // Ensure the root is a JSON object
    if (!_document.IsObject()) {
        throw std::runtime_error("Profile manifest JSON is not an object.");
    }

    // Validate the JSON against the schema
    JSONSchemaValidator::validate_schema(_json_str, _json_schema);
}

// Returns a Profile object constructed from the parsed JSON.
// Throws runtime_error if required fields are missing or invalid.
const profile::Profile JSONManifestReader::get_profile() {
    profile::Profile prof{};

    if (!_document.IsObject())
        throw std::runtime_error("root is not object");

    // Validate presence and type of "hyprprof"
    if (!_document.HasMember("hyprprof") || !_document["hyprprof"].IsObject())
        throw std::runtime_error("hyprprof missing or invalid");

    // Validate presence and type of "version_constraints"
    if (!_document.HasMember("version_constraints") || !_document["version_constraints"].IsObject())
        throw std::runtime_error("version_constraints missing or invalid");

    const auto& versions = _document["version_constraints"];
    const auto& hyprprof = _document["hyprprof"];

    // Populate the Profile object with metadata
    prof.set_name(hyprprof["name"].GetString())
        .set_version(hyprprof["version"].GetString())
        .set_description(hyprprof["description"].GetString())
        .set_wayland_version(versions["wayland"].GetString())
        .set_hyprland_version(versions["hyprland"].GetString());

    return prof;
}

// Returns a list of DotFile objects representing the dotfiles in the JSON.
// Handles environment variable expansion for "$DOTCONFIG" and "~".
const std::list<core::DotFile> JSONManifestReader::get_dotconfigs() {
    std::list<core::DotFile> dotconfigs;

    // If "dotfiles" is missing or not an object, return an empty list
    if (!_document.HasMember("dotfiles") || !_document["dotfiles"].IsObject())
        return dotconfigs;

    const auto& dotfiles = _document["dotfiles"].GetObject();

    // Iterate over all dotfile entries
    for (auto it = dotfiles.MemberBegin(); it != dotfiles.MemberEnd(); ++it) {
        const char* name = it->name.GetString();
        const auto& value = it->value;

        core::DotFile dot;
        dot.set_name(name);

        // Optional: set "pack" if present and is a string
        if (value.HasMember("pack") && value["pack"].IsString())
            dot.set_pack(value["pack"].GetString());

        // Optional: set target path if present and is a string
        if (value.HasMember("target") && value["target"].IsString()) {
            std::string target = value["target"].GetString();

            // Resolve "$DOTCONFIG" and "~" to actual paths
            const std::string dotconfig_path = hprof_fs::dotconfig::get_config_path();

            if (target.rfind("$DOTCONFIG", 0) == 0) {
                target.replace(0, std::string("$DOTCONFIG").size(), dotconfig_path);
            } else if (target.rfind("~/", 0) == 0) {
                target.replace(0, 1, std::getenv("HOME"));
            }

            dot.set_target_path(target);
        }

        // Optional: set source path if present and is a string
        if (value.HasMember("source") && value["source"].IsString())
            dot.set_source_path(value["source"].GetString());

        // Add the DotFile to the list
        dotconfigs.push_back(dot);
    }

    return dotconfigs;
}

} // namespace json
