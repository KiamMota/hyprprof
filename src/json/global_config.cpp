#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "json/global_config.hpp"
#include <string>

json::GlobalConfig::GlobalConfig()
{
}

void json::GlobalConfig::set_json_context(const std::string& json)
{
  _json_str = json;
  _document.Parse(json.c_str());
}

const std::string json::GlobalConfig::username() const noexcept
{
  if(_document.HasMember("username"))
    return _document["username"].GetString();
  return {};
}

const std::string json::GlobalConfig::current_profile() const noexcept
{
  if(_document.HasMember("current_profile"))
    return _document["current_profile"].GetString();
  return {};
}
void json::GlobalConfig::remake_json() {

  _document["username"].SetString(_username.c_str(), _document.GetAllocator());
  _document["current_profile"].SetString(_current_profile.c_str(), _document.GetAllocator());
}

void json::GlobalConfig::create_json()
{
  _document.SetObject();  // trabalha direto no document interno
    rapidjson::Document::AllocatorType& alloc = _document.GetAllocator();

    _document.AddMember("username", rapidjson::Value().SetString(_username.c_str(), alloc), alloc);
    _document.AddMember("current_profile",
                        rapidjson::Value().SetString(_current_profile.c_str(), alloc),
                        alloc);

    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    _document.Accept(writer);

    _json_str = buffer.GetString();
}

json::GlobalConfig& json::GlobalConfig::set_current_profile(const std::string& prof) 
{
  _current_profile = prof;
  return *this;
}

json::GlobalConfig& json::GlobalConfig::set_username(const std::string& user)
{
  _username = user;
  return *this;
}

const std::string& json::GlobalConfig::to_string() const
{
  return _json_str;
}
