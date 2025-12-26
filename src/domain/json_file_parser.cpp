#include "domain/json_file_parser.hpp"

#include "infra/log/json_log.hpp"
#include <iostream>
#include <rapidjson/error/en.h>
#include <unistd.h>

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

bool json::JsonFileParser::_HaveHyprprofObject() {
    if (!_HaveObject("hyprprof")) {
        json::log::object_not_found("hyprprof");
        return false;
    }
    hyprpof = _GetObject("hyprprof");
    return true;
}

bool json::JsonFileParser::_HavePayload() {
    if (!hyprpof.HasMember("required_payload"))
        return false;
    if (!hyprpof["required_payload"].IsBool())
        return false;
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

json::JsonFileParser::JsonFileParser() : schema("0.1") {}

void json::JsonFileParser::Parse(const std::string& json_str) {

    if (json_str.empty()) {
        json::log::err("the json content is empty!");
        return;
    }

    _json_file_str = json_str;

    if (!_TryJsonParse())
        return;
    if (!_ValidateSchema())
        return;
    if (!_HaveHyprprofObject())
        return;
    if (!_HaveAppsObject())
        return;
    if (!_HaveRequiredApps())
        return;
    _havePayload = _HavePayload();
}

bool json::JsonFileParser::hasPayload() { return _havePayload; }

std::string json::JsonFileParser::json_str() const { return _json_file_str; }
