#include "json/json_base.hpp"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include "rapidjson/error/error.h"
#include "json/json_exceptions.hpp"
#include <list>

static const std::string get_string_type(const rapidjson::Value& value) {
    switch (value.GetType()) {
    case rapidjson::kNullType:
        return "null";
    case rapidjson::kFalseType:
    case rapidjson::kTrueType:
        return "bool";
    case rapidjson::kObjectType:
        return "object";
    case rapidjson::kArrayType:
        return "array";
    case rapidjson::kStringType:
        return "string";
    case rapidjson::kNumberType:
        return "number";
    default:
        return "unknown";
    }
}

json::JSONBase::JSONBase(const rapidjson::Value* node) : _node(node) {}

json::JSONBase::JSONBase(const std::string& json) { _json_str = json; }

void json::JSONBase::parse() {
    if (_json_str.empty())
        throw JsonEmptyException();
    rapidjson::ParseResult result = _document.Parse(_json_str.c_str());
    if (!result) {
        size_t error_offset = result.Offset();
        size_t line = 1, col = 1;
        for (size_t i = 0; i < error_offset && i < _json_str.size(); ++i) {
            if (_json_str[i] == '\n') {
                line++;
                col = 1;
            } else
                col++;
        }

        std::string expected =
            "Expected a valid JSON value (object, array, string, number, true, false, null)";
        std::string msg = std::string("JSON parse error: ") +
                          rapidjson::GetParseError_En(result.Code()) + " at line " +
                          std::to_string(line) + ", column " + std::to_string(col) + ". " +
                          expected;

        throw JsonParseException(msg, line, col);
    }
}

json::JSONBase json::JSONBase::get_in(const std::string& f) const {
    if (!_node->HasMember(f.c_str()))
        throw JsonSearchTypeException(f.c_str(), "none", "object");
    const rapidjson::Value& val = (*_node)[f.c_str()];
    if (!val.IsObject())
        throw JsonSearchTypeException(f.c_str(), get_string_type(val).c_str(), "object");
    return JSONBase(&val);
}

void json::JSONBase::set_json_string(const std::string& json) {
    if (json.empty())
        throw JsonEmptyException();
    _json_str = json;
}

const std::string& json::JSONBase::json_str() const noexcept { return _json_str; }

const std::string json::JSONBase::get_string(const std::string& n) const {
    if (!_document.HasMember(n.c_str())) {
        throw JsonSearchFieldNotFoundException(n.c_str());
    }

    const rapidjson::Value& value = _document[n.c_str()];
    if (!value.IsString()) {
        throw JsonSearchTypeException(n.c_str(), get_string_type(value).c_str(), "string");
    }
    return value.GetString();
}

const bool json::JSONBase::get_bool(const std::string& f) const {
    if (!_document.HasMember(f.c_str()))
        throw JsonSearchFieldNotFoundException(f.c_str());
    const rapidjson::Value& value = _document[f.c_str()];
    if (!value.IsBool())
        throw JsonSearchTypeException(f.c_str(), get_string_type(value).c_str(), "bool");
    return value.GetBool();
}

const int json::JSONBase::get_int(const std::string& f) const {
    if (!_document.HasMember(f.c_str()))
        throw JsonSearchFieldNotFoundException(f.c_str());
    const rapidjson::Value& val = _document[f.c_str()];
    if (!val.IsInt() && !val.IsInt64())
        throw JsonSearchTypeException(f.c_str(), get_string_type(val).c_str(), "int");
    return val.GetInt();
}

const std::list<std::string> json::JSONBase::get_string_array(const std::string& f) const {
    std::list<std::string> result;

    if (!_document.HasMember(f.c_str()))
        return result; // retorna lista vazia se o campo não existe

    const rapidjson::Value& val = _document[f.c_str()];

    if (!val.IsArray())
        throw JsonSearchTypeException(f.c_str(), get_string_type(val).c_str(), "array");

    for (const auto& item : val.GetArray()) {
        if (!item.IsString())
            throw JsonSearchTypeException(f.c_str(), get_string_type(item).c_str(),
                                          "string in array");
        result.push_back(item.GetString());
    }

    return result;
}
