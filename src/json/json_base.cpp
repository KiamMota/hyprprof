#include "json/json_base.hpp"
#include "rapidjson/document.h"
#include "rapidjson/error/en.h"
#include "rapidjson/error/error.h"
#include "json/json_exceptions.hpp"
#include <cstdlib>

const rapidjson::Document& json::JSONBase::document() const
{
 return _document;
}

void json::JSONBase::set_json_string(const std::string& json_str)
{
  if(json_str.empty())
    throw JsonEmptyException();
  _json_str = json_str;
}

const std::string& json::JSONBase::json_str() const noexcept
{
  return _json_str;
}

json::JSONBase::JSONBase(const std::string& json) { _json_str = json;  }

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

