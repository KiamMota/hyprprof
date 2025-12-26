#include "domain/install/json_file_parser.hpp"

#include <rapidjson/error/en.h>
#include <unistd.h>


bool domain::install::JsonFileParser::_TryJsonParse() {
    return !d.Parse(_json_file_str.c_str()).HasParseError();
}

bool domain::install::JsonFileParser::_HaveObject(const std::string& name) {
    return d.IsObject()
        && d.HasMember(name.c_str())
        && d[name.c_str()].IsObject();
}

rapidjson::Value& domain::install::JsonFileParser::_GetObject(const std::string& name) {
    return d[name.c_str()];
}

bool domain::install::JsonFileParser::_ValidateSchema() {
    return d.HasMember("schema") && d["schema"].IsString();
}

bool domain::install::JsonFileParser::_HaveAppsObject() {
    if (!_HaveObject("apps"))
        return false;
    apps = _GetObject("apps");
    return true;
}

bool domain::install::JsonFileParser::_HaveHyprprofObject() {
    if (!_HaveObject("hyprprof"))
        return false;
    hyprprof = _GetObject("hyprprof");
    return true;
}

bool domain::install::JsonFileParser::_HavePayload() const {
    return hyprprof.HasMember("required_payload");
}


bool domain::install::JsonFileParser::_HaveRequiredApps() {
    return apps.HasMember("browser")
        && apps.HasMember("file_manager");
}

domain::install::JsonFileParser::JsonFileParser() : schema("0.1") {}

domain::install::JsonFileParserError domain::install::JsonFileParser::Parse(const std::string& json_str) {

    if (json_str.empty())
        return JsonFileParserError::EmptyJSON;

    _json_file_str = json_str;

    if (!_TryJsonParse())
        return JsonFileParserError::ParsingError;

    if (!_ValidateSchema())
        return JsonFileParserError::NoSchema;

    if (!_HaveHyprprofObject())
        return JsonFileParserError::NoHyprProfObject;

    if (!_HaveAppsObject())
        return JsonFileParserError::NoAppsObject;

    if (!_HaveRequiredApps())
        return JsonFileParserError::NoAppsObject;

    return JsonFileParserError::NoError;
}

bool domain::install::JsonFileParser::hasPayload() const 
{ 
  return _HavePayload();  
}

std::string domain::install::JsonFileParser::json_str() const { return _json_file_str; }
