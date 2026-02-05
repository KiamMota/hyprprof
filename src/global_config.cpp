#include "fs/file.hpp"
#include "hyprprof_path.hpp"
#include "rapidjson/document.h"
#include "global_config.hpp"
#include <stdexcept>
#include <string>

core::GlobalConfig::GlobalConfig()
{
}

const std::string core::GlobalConfig::get_config_content()
{
  std::string path = HyprprofPath::hyprprof_path() + "/config.json";
  if(!fs::file::exists(path))
    throw std::runtime_error("config.json doesn't exists!");
  return fs::file::get_content(path);
}

const std::string core::GlobalConfig::get_current_profile_name()
{
  std::string json = get_config_content();
  rapidjson::Document doc;
  doc.Parse(json.c_str());
  return doc["username"].GetString();
}

const std::string core::GlobalConfig::get_username()
{
  std::string json = get_config_content();
  rapidjson::Document doc;
  doc.Parse(json.c_str());
  return doc["current_profile"].GetString();
}
