#include "json/json_manifest_reader.hpp"
#include "dotconfig.hpp"
#include "profile/profile_model.hpp"
#include "json/json_schema.hpp"
#include "json/json_schema_validator.hpp"
#include <list>
#include <string>
#include <unistd.h>

json::JSONManifestReader::JSONManifestReader() { _json_schema = HYPRPROF_JSON_SCHEMA; }

void json::JSONManifestReader::run(const std::string& json_str) {
    _json_str = json_str;
    _document.Parse(_json_str.c_str());
    
    JSONSchemaValidator::validate_schema(_json_str, _json_schema);
}

const profile::Profile json::JSONManifestReader::get_profile() {
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

const std::list<core::Dotconfig> json::JSONManifestReader::get_dotconfigs()
{
    std::list<core::Dotconfig> dotconfigs;

    if (!_document.HasMember("dotfiles") || !_document["dotfiles"].IsObject())
        return dotconfigs; // lista vazia se não existir

    const auto& dotfiles = _document["dotfiles"].GetObject();

    for (auto it = dotfiles.MemberBegin(); it != dotfiles.MemberEnd(); ++it)
    {
        const char* name = it->name.GetString();
        const auto& value = it->value;

        core::Dotconfig dot;
        dot.set_name(name);

        if (value.HasMember("pack") && value["pack"].IsString())
            dot.set_pack(value["pack"].GetString());

        if (value.HasMember("target") && value["target"].IsString())
            dot.set_target_path(value["target"].GetString());

        if (value.HasMember("source") && value["source"].IsString())
            dot.set_source_path(value["source"].GetString());

        dotconfigs.push_back(dot);
    }

    return dotconfigs;
}


