#include "json/json_file_parser.hpp"
#include "fs.hpp"

#include "json/log.hpp"
#include <iostream>
#include <rapidjson/error/en.h>


bool json::JsonFileParser::_TryJsonParse() {
    rapidjson::ParseResult ok = d.Parse(_json_file_str.c_str());
    if (!ok) {
        std::cout << "JSON ERR PARSE: " << rapidjson::GetParseError_En(ok.Code()) << "\n"
                  << "in: " << ok.Offset() << "\n";
        return false;
    }
    return true;
}

bool json::JsonFileParser::_HaveObject(const std::string& name) {
    if (!d.IsObject())
        return false;
    if (!d.HasMember(name.c_str()))
        return false;
    return d[name.c_str()].IsObject();
}

rapidjson::Value& json::JsonFileParser::_GetObject(const std::string& name) {
    return d[name.c_str()];
}

bool json::JsonFileParser::_ValidateSchema() {
    if (!d.HasMember("schema")) {
        std::cerr << "schema not found.\n";
        return false;
    }

    if (!d["schema"].IsString()) {
        std::cerr << "schema is not string.\n";
        return false;
    }
    return true;
}

bool json::JsonFileParser::_HaveAppsObject() {
    if (!_HaveObject("apps")) {
      json::log::object_not_found("apps");
        return false;
    }
    apps = _GetObject("apps");
    return true;
}

bool json::JsonFileParser::_HaveEnvironmentObject() {
    if (!_HaveObject("environment")) {
    json::log::object_not_found("apps");
        return false;
    }
    environment = _GetObject("environment");
    return true;
}

bool json::JsonFileParser::_HaveAppsTerminalObject() {
    if (!apps.HasMember("terminal") || !apps["terminal"].IsObject()) {
      json::log::member_not_found("apps", "terminal");  
      return false;
    }
    return true;
}

bool json::JsonFileParser::_HaveRequiredApps() {
    if (!apps.HasMember("browser")) {
      json::log::member_not_found("apps", "browser");
        return false;
    }
    if (!apps.HasMember("file_manager")) {
      json::log::member_not_found("apps", "file_manager");
        return false;
    }
    return true;
}

json::JsonFileParser::JsonFileParser(const std::string& file_path) : schema("0.1") {
    _json_file_str = fs::get_file_content(file_path);
}

void json::JsonFileParser::Parse() {
    if (!_TryJsonParse())
        return;
    if (!_ValidateSchema())
        return;
    if (!_HaveAppsObject())
        return;
    if (!_HaveRequiredApps())
        return;
}

std::string json::JsonFileParser::json_str() const { return _json_file_str; }
