#include "json/json_manifest_reader.hpp"
#include "json/json_schema.hpp"
#include "json/json_schema_validator.hpp"
#include <string>
#include <unistd.h>

json::JSONManifestReader::JSONManifestReader() { _json_schema = HYPRPROF_JSON_SCHEMA; }

void json::JSONManifestReader::run(const std::string& json_str) {
    _json_str = json_str;
    _document.Parse(_json_str.c_str());
    
    JSONSchemaValidator::validate_schema(_json_str, _json_schema);
}

profile::Profile json::JSONManifestReader::get_profile() {
    profile::Profile prof{};

    if (!_document.IsObject())
        throw std::runtime_error("root is not object");

    if (!_document.HasMember("hyprprof") || !_document["hyprprof"].IsObject())
        throw std::runtime_error("hyprprof missing or invalid");

    if (!_document.HasMember("version_constraints") || !_document["version_constraints"].IsObject())
        throw std::runtime_error("version_constraints missing or invalid");

    const auto& versions = _document["version_constraints"];
    const auto& hyprprof = _document["hyprprof"];
    prof.set_name(hyprprof["name"].GetString())
        .set_version(hyprprof["version"].GetString())
        .set_description(hyprprof["description"].GetString())
        .set_wayland_version(versions["wayland"].GetString())
        .set_hyprland_version(versions["hyprland"].GetString());

    return prof;
}
