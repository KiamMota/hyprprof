#include "fs/file.hpp"
#include "hyprprof_path.hpp"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include "global_config.hpp"
#include <stdexcept>
#include <string>

core::GlobalConfig::GlobalConfig()
{
}

const std::string core::GlobalConfig::get_config_content()
{
  std::string path = HyprprofPath::config_path();
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

void core::GlobalConfig::set_file_content(const std::string &content)
{
  fs::file::overwrite(HyprprofPath::config_path(), content);
}

void core::GlobalConfig::change_username(const std::string &name)
{
    std::string json = get_config_content();
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    if (!doc.HasMember("username"))
        doc.AddMember("username", "", doc.GetAllocator());

    doc["username"].SetString(name.c_str(), doc.GetAllocator());

    // PrettyWriter para JSON legível
    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    set_file_content(buffer.GetString());
}

void core::GlobalConfig::change_current_profile(const std::string &curr)
{
    std::string json = get_config_content();
    rapidjson::Document doc;
    doc.Parse(json.c_str());

    if (!doc.HasMember("current_profile"))
        doc.AddMember("current_profile", "", doc.GetAllocator());

    doc["current_profile"].SetString(curr.c_str(), doc.GetAllocator());

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    set_file_content(buffer.GetString());
}

void core::GlobalConfig::create_file_content(const std::string &username, const std::string &current_profile)
{
    rapidjson::Document doc;
    doc.SetObject(); 
    rapidjson::Document::AllocatorType& allocator = doc.GetAllocator();

    doc.AddMember("username", rapidjson::Value(username.c_str(), allocator), allocator);
    doc.AddMember("current_profile", rapidjson::Value(current_profile.c_str(), allocator), allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    set_file_content(buffer.GetString());
}

