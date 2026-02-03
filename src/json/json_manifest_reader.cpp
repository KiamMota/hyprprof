#include "json/json_manifest_reader.hpp"
#include "json/json_base.hpp"
#include "json/json_exceptions.hpp"
#include "json/json_schema.hpp"
#include "json/json_schema_validator.hpp"
#include <string>
#include <unistd.h>

json::JSONManifestReader::JSONManifestReader() : JSONBase() { _json_schema = HYPRPROF_JSON_SCHEMA; }

void json::JSONManifestReader::run() {
    if (json_str().empty())
        throw JsonEmptyException();
    parse();
    JSONSchemaValidator::JSONSchemaValidator::validate_schema(json_str(), _json_schema);
}

profile::Profile json::JSONManifestReader::get_profile() {
    profile::Profile prof{};

    const auto& doc = document();

    if (!doc.IsObject())
        throw std::runtime_error("root is not object");

    if (!doc.HasMember("hyprprof") || !doc["hyprprof"].IsObject())
        throw std::runtime_error("hyprprof missing or invalid");

    if (!doc.HasMember("version_constraints") || !doc["version_constraints"].IsObject())
        throw std::runtime_error("version_constraints missing or invalid");

    const auto& versions = doc["version_constraints"];
    const auto& hyprprof = doc["hyprprof"];
    prof.set_name(hyprprof["name"].GetString())
        .set_version(hyprprof["version"].GetString())
        .set_description(hyprprof["description"].GetString())
        .set_wayland_version(versions["wayland"].GetString())
        .set_hyprland_version(versions["hyprland"].GetString());

    return prof;
}
