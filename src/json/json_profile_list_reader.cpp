#include "json/json_profile_list_reader.hpp"
#include "infra/json.hpp"
#include "rapidjson/document.h"
#include <stdexcept>

json::JSONProfileListReader::JSONProfileListReader(const std::string& json_src)
{
  if(json_src.empty())
    throw std::runtime_error("json source is empty");
  infra::json::is_json_valid(json_src);
  rapidjson::Document doc;
  doc.Parse(json_src.c_str());
}

const std::string json::JSONProfileListReader::current_profile_name() const noexcept
{
  return doc["current_profile"].GetString();
}

const std::string json::JSONProfileListReader::current_profile_path() const noexcept
{
  return doc["current_path"].GetString();
}
