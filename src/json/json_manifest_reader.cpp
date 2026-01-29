#include "json/json_manifest_reader.hpp"
#include "json/json_schema.hpp"
#include "infra/json.hpp"
#include "rapidjson/document.h"
#include <list>
#include <rapidjson/error/en.h>
#include <stdexcept>
#include <string>
#include <unistd.h>

json::JSONManifestReader::JSONManifestReader() {

    _json_schema = HYPRPROF_JSON_SCHEMA;
}

void json::JSONManifestReader::set_json_str(const std::string& json_str)
{
  _json_str = json_str;
}

bool json::JSONManifestReader::parse() {
    if (_json_str.empty())
        throw std::runtime_error("empty JSON");

    doc.Parse(_json_str.c_str());

    return infra::json::validate_schema(_json_str, _json_schema);
}

std::string json::JSONManifestReader::version() {
    const rapidjson::Value& hyprprof_obj = doc["hyprprof"];
    return hyprprof_obj["version"].GetString();
}

std::string json::JSONManifestReader::profile_name() {
    const rapidjson::Value& hyprprof_obj = doc["hyprprof"];
    return hyprprof_obj["name"].GetString();
}

std::list<std::string> json::JSONManifestReader::authors() {
    std::list<std::string> result;

    const auto& hyprprof = doc["hyprprof"];
    const auto& authors = hyprprof["authors"];

    for (const auto& a : authors.GetArray()) {
        result.emplace_back(a.GetString());
    }

    return result;
}

profile::Profile json::JSONManifestReader::get_profile() {
    profile::Profile prof{};

    // Exemplo: assumindo que você tem métodos para pegar os campos do JSON
    prof.set_name(profile_name())
        .set_version(version())
        .set_description(desciption()).set_authors(authors())
        .set_wayland_version(wayland_version())
        .set_hyprland_version(hyprland_version());

    return prof;
}

std::string json::JSONManifestReader::hyprland_version() {
    const rapidjson::Value& version_constraints_obj = doc["version_constraints"];
    return version_constraints_obj["hyprland"].GetString();
}

std::string json::JSONManifestReader::wayland_version() {
    const rapidjson::Value& version_constraits_obj = doc["version_constraints"];
    return version_constraits_obj["wayland"].GetString();
}

std::string json::JSONManifestReader::desciption() {
    const rapidjson::Value& hyprprof_obj = doc["hyprprof"];
    return hyprprof_obj["description"].GetString();
}
