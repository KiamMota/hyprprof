#include "core/install/json_manifest_validator.hpp"

#include <rapidjson/error/en.h>
#include <unistd.h>


bool core::install::JsonFileParser::_TryJsonParse() {
    return !d.Parse(_json_file_str.c_str()).HasParseError();
}

bool core::install::JsonFileParser::_HaveObject(const std::string& name) {
    return d.IsObject()
        && d.HasMember(name.c_str())
        && d[name.c_str()].IsObject();
}

rapidjson::Value& core::install::JsonFileParser::_GetObject(const std::string& name) {
    return d[name.c_str()];
}

bool core::install::JsonFileParser::_ValidateSchema() {
    return d.HasMember("schema") && d["schema"].IsString();
}

core::install::JsonFileParserError core::install::JsonFileParser::_ValidateRunScripts() const
{
    if (!hyprprof.HasMember("run_scripts")) return JsonFileParserError::NoError;

    const auto& arr = hyprprof["run_scripts"];
    if (!arr.IsArray())
      return JsonFileParserError::TypeError;

    if (arr.Empty())
      return JsonFileParserError::EmptyOrNullValue;
    for (auto& v : arr.GetArray())
        if (!v.IsString())
      return JsonFileParserError::TypeError;
    return JsonFileParserError::NoError;
}

void core::install::JsonFileParser::_PopulateScripts()
{
  _scripts.clear();
    for (auto& v : hyprprof["run_scripts"].GetArray())
        _scripts.push_back(v.GetString());
}

bool core::install::JsonFileParser::_HaveHyprprofObject() {
    if (!_HaveObject("hyprprof"))
        return false;
    hyprprof = _GetObject("hyprprof");
    return true;
}

bool core::install::JsonFileParser::_HavePayload() const {
    return hyprprof.HasMember("required_payload");
}

core::install::JsonFileParser::JsonFileParser() : schema("0.1") {}

core::install::JsonFileParserError core::install::JsonFileParser::Parse(const std::string& json_str) {

    if (json_str.empty())
        return JsonFileParserError::EmptyJSON;

    _json_file_str = json_str;

    if (!_TryJsonParse())
        return JsonFileParserError::ParsingError;

    if (!_ValidateSchema())
        return JsonFileParserError::NoSchema;

    if (!_HaveHyprprofObject())
        return JsonFileParserError::NoHyprProfObject;
    
    JsonFileParserError run_scripts_res = _ValidateRunScripts();
  
    if(run_scripts_res == JsonFileParserError::NoError) _PopulateScripts();

    return JsonFileParserError::NoError;
}

bool core::install::JsonFileParser::hasPayload() const 
{ 
  return _HavePayload();  
}

std::list<std::string> core::install::JsonFileParser::scripts()
{
  return _scripts;
}

std::string core::install::JsonFileParser::profile_name() const
{
  return hyprprof["profile_name"].GetString();
}

std::string core::install::JsonFileParser::version() const
{
  return hyprprof["version"].GetString();
}

std::string core::install::JsonFileParser::json_str() const { return _json_file_str; }
