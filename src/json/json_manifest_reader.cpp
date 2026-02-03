#include "json/json_manifest_reader.hpp"
#include "json/json_base.hpp"
#include "json/json_schema.hpp"
#include "json/json_schema_validator.hpp"
#include <string>
#include <unistd.h>

json::JSONManifestReader::JSONManifestReader() : JSONBase() {

    _json_schema = HYPRPROF_JSON_SCHEMA;
    JSONSchemaValidator::validate_schema(json_str(), _json_schema);
}

void json::JSONManifestReader::set_json_string(const std::string& json_str)
{
  set_base_json_string(_json_schema);
}

profile::Profile json::JSONManifestReader::get_profile() {
    profile::Profile prof{};

    prof.set_name(get_in("hyprprof").get_string("profile_name"))
        .set_version(get_in("hyprprof").get_string("version"))
        .set_description(get_in("hyprprof").get_string("description"))
        .set_wayland_version(get_in("version_constraints").get_string("wayland"))
        .set_hyprland_version(get_in("version_constraints").get_string("hyprland"));
    return prof;
}

