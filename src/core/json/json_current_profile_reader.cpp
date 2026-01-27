#include "core/json/json_current_profile_reader.hpp"
#include "infra/json.hpp"
#include "rapidjson/document.h"
#include <stdexcept>

core::json::JSONCurrentProfileReader::JSONCurrentProfileReader(const std::string& json_src)
{
  if(json_src.empty())
    throw std::runtime_error("json source is empty");
  infra::json::is_json_valid(json_src);
  rapidjson::Document doc;
  doc.Parse(json_src.c_str());
}

const std::string core::json::JSONCurrentProfileReader::current_profile_name() const noexcept
{
  return doc["current_profile"].GetString();
}

const std::string core::json::JSONCurrentProfileReader::current_profile_path() const noexcept
{
  return doc["current_path"].GetString();
}
