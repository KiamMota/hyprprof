#include "fs/file.hpp"
#include "hyprprof_path.hpp"
#include "rapidjson/document.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"
#include "config_file.hpp"
#include <stdexcept>
#include <string>

core::ConfigFile::ConfigFile()
{
}

const std::string core::ConfigFile::get_content()
{
  std::string path = HyprprofPath::config_path();
  if(!hprof_fs::file::exists(path))
    throw std::runtime_error("config.json doesn't exists!");
  return hprof_fs::file::get_content(path);
}

const std::string core::ConfigFile::get_current_profile_name()
{
  std::string json = get_content();
  rapidjson::Document doc;
  doc.Parse(json.c_str());
  return doc["current_profile"].GetString();
}

const std::string core::ConfigFile::get_username()
{
  std::string json = get_content();
  rapidjson::Document doc;
  doc.Parse(json.c_str());
  return doc["username"].GetString();
}

void core::ConfigFile::set_file_content(const std::string &content)
{
  hprof_fs::file::overwrite(HyprprofPath::config_path(), content);
}

void core::ConfigFile::change_username(const std::string &name)
{
    std::string json = get_content();
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

void core::ConfigFile::change_current_profile(const std::string &curr)
{
    std::string json;
    if (hprof_fs::file::exists(HyprprofPath::config_path()))
        json = get_content();

    rapidjson::Document doc;
    if (json.empty() || doc.Parse(json.c_str()).HasParseError())
        doc.SetObject(); // arquivo vazio ou inválido → criar objeto novo

    auto& allocator = doc.GetAllocator();

    if (!doc.HasMember("current_profile"))
        doc.AddMember("current_profile", rapidjson::Value(curr.c_str(), allocator), allocator);
    else
        doc["current_profile"].SetString(curr.c_str(), allocator);

    // Se não existir username, adiciona vazio
    if (!doc.HasMember("username"))
        doc.AddMember("username", "", allocator);

    rapidjson::StringBuffer buffer;
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
    doc.Accept(writer);

    set_file_content(buffer.GetString());
}


void core::ConfigFile::create_file_content(const std::string &username, const std::string &current_profile)
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

