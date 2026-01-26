#include "core/json/json_manifest_reader.hpp"
#include "core/json/json_schema.hpp"
#include "core/profile/profile.hpp"
#include "core/profile/profile_assembler.hpp"
#include "infra/json.hpp"
#include "rapidjson/document.h"
#include <list>
#include <rapidjson/error/en.h>
#include <stdexcept>
#include <string>
#include <unistd.h>

core::json::JSONManifestReader::JSONManifestReader(const std::string& json_str) {

    _json_schema = HYPRPROF_JSON_SCHEMA;
    _json_str = json_str;
}

bool core::json::JSONManifestReader::parse() {
    if (_json_str.empty())
        throw std::runtime_error("empty JSON");

    doc.Parse(_json_str.c_str());

    return infra::json::validate_schema(_json_str, _json_schema);
}

std::string core::json::JSONManifestReader::version() {
    const rapidjson::Value& hyprprof_obj = doc["hyprprof"];
    return hyprprof_obj["version"].GetString();
}

std::string core::json::JSONManifestReader::profile_name() {
    const rapidjson::Value& hyprprof_obj = doc["hyprprof"];
    return hyprprof_obj["name"].GetString();
}

std::list<std::string> core::json::JSONManifestReader::authors() {
    std::list<std::string> result;

    const auto& hyprprof = doc["hyprprof"];
    const auto& authors = hyprprof["authors"];

    for (const auto& a : authors.GetArray()) {
        result.emplace_back(a.GetString());
    }

    return result;
}

core::profile::ProfileAssembler core::json::JSONManifestReader::GetProfile() {
    profile::ProfileAssembler prof{};

    return prof;
}

std::string core::json::JSONManifestReader::hyprland_version() {
    const rapidjson::Value& version_constraints_obj = doc["version_constraints"];
    return version_constraints_obj["hyprland"].GetString();
}

std::string core::json::JSONManifestReader::wayland_version() {
    const rapidjson::Value& version_constraits_obj = doc["version_constraints"];
    return version_constraits_obj["wayland"].GetString();
}

std::string core::json::JSONManifestReader::desciption() {
    const rapidjson::Value& hyprprof_obj = doc["hyprprof"];
    return hyprprof_obj["description"].GetString();
}
