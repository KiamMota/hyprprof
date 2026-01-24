#include "core/json_manifest.hpp"
#include "core/json_schemas.hpp"
#include "core/profile/profile.hpp"
#include "infra/json.hpp"
#include "infra/log.hpp"
#include "rapidjson/document.h"
#include <list>
#include <rapidjson/error/en.h>
#include <stdexcept>
#include <string>
#include <unistd.h>

core::JsonManifest::JsonManifest(const std::string& json_str) {

  _json_schema = HYPRPROF_JSON_SCHEMA;

  if(json_str.empty())
    throw std::runtime_error("empty JSON!");
  _json_str = json_str;
  doc.Parse(_json_str.c_str());
}

void core::JsonManifest::parse()
{
  
  if(infra::json::validate_schema(_json_str, _json_schema))
  {
    infra::hypr_log::log("validated json!");
    return;
  }
  infra::hypr_log::err("invalid json!");
}

std::string core::JsonManifest::profile_name()
{
  const rapidjson::Value& hyprprof_obj = doc["hyprprof"]; 
  return hyprprof_obj["name"].GetString();
}

std::list<std::string> core::JsonManifest::authors()
{
    std::list<std::string> result;

    const auto& hyprprof = doc["hyprprof"];
    const auto& authors = hyprprof["authors"];

    for (const auto& a : authors.GetArray())
    {
        result.emplace_back(a.GetString());
    }

    return result;
}

core::profile::Profile core::JsonManifest::GetProfile()
{
  profile::Profile prof{};

  prof.set_name(profile_name());
  prof.set_authors(authors());
  prof.set_description(desciption());
  prof.set_version(version());
  
  return prof;
}

std::string core::JsonManifest::desciption()
{
  const rapidjson::Value& hyprprof_obj = doc["hyprprof"]; 
  return hyprprof_obj["description"].GetString();
}


