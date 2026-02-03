#include "json/json_manifest_reader.hpp"
#include "json/json_base.hpp"
#include "json/json_schema.hpp"
#include "json/json_schema_validator.hpp"
#include <string>
#include <unistd.h>

json::JSONManifestReader::JSONManifestReader() : JSONBase() {
    _json_schema = HYPRPROF_JSON_SCHEMA;
}

void json::JSONManifestReader::run() const
{

    JSONSchemaValidator::JSONSchemaValidator::validate_schema(json_str(), _json_schema);
}

profile::Profile json::JSONManifestReader::get_profile() {
    profile::Profile prof{};

    const auto& doc = document();

    // validações estruturais mínimas (implícitas pelo uso correto)
    const auto& hyprprof = doc["hyprprof"];
    const auto& versions = doc["version_constraints"];

    prof
        .set_name(hyprprof["name"].GetString())
        .set_version(hyprprof["version"].GetString())
        .set_description(hyprprof["description"].GetString())
        .set_wayland_version(versions["wayland"].GetString())
        .set_hyprland_version(versions["hyprland"].GetString());

    return prof;
}


