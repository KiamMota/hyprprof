#include "infra/json.hpp"
#include "rapidjson/document.h"
#include "rapidjson/schema.h"
#include <stdexcept>

bool infra::json::is_json_valid(const std::string& json) {
    rapidjson::Document doc;
    rapidjson::ParseResult result = doc.Parse(json.c_str());

    if (!result) {
        size_t error_offset = result.Offset();
        size_t line = 1, col = 1;
        for (size_t i = 0; i < error_offset && i < json.size(); ++i) {
            if (json[i] == '\n') { line++; col = 1; }
            else col++;
        }

        std::string expected = "Expected a valid JSON value (object, array, string, number, true, false, null)";
        std::string msg = std::string("JSON parse error: ") + rapidjson::GetParseError_En(result.Code()) +
                          " at line " + std::to_string(line) +
                          ", column " + std::to_string(col) +
                          ". " + expected;

        throw infra::json::JsonParseException(msg, line, col);
    }

    return true;
}


bool infra::json::validate_schema(const std::string &json, const std::string &json_schema)
{
    if (!infra::json::is_json_valid(json))
        throw std::runtime_error("Invalid JSON content.");

    if (!infra::json::is_json_valid(json_schema))
        throw std::runtime_error("Invalid JSON Schema.");

    rapidjson::Document schema_doc;
    if (schema_doc.Parse(json_schema.c_str()).HasParseError())
        throw std::runtime_error(
            std::string("Schema parse error: ") +
            rapidjson::GetParseError_En(schema_doc.GetParseError())
        );

    rapidjson::SchemaDocument sd(schema_doc);
    rapidjson::SchemaValidator validator(sd);

    rapidjson::Document doc;
    if (doc.Parse(json.c_str()).HasParseError())
        throw std::runtime_error(
            std::string("JSON parse error: ") +
            rapidjson::GetParseError_En(doc.GetParseError())
        );

    if (!doc.Accept(validator))
        throw std::runtime_error("JSON does not match the schema.");

    return true; 
}

