#include "json/json_schema_validator.hpp"
#include <rapidjson/document.h>
#include <rapidjson/schema.h>
#include <rapidjson/error/en.h>
#include <stdexcept>


void json::JSONSchemaValidator::validate_schema(const std::string &json_str, const std::string &schema_str)
{
    // 1. Parse JSON
    rapidjson::Document json;
    if (json.Parse(json_str.c_str()).HasParseError()) {
        throw std::runtime_error(
            std::string("Invalid JSON: ") + rapidjson::GetParseError_En(json.GetParseError())
        );
    }

    // 2. Parse Schema
    rapidjson::Document schema_doc;
    if (schema_doc.Parse(schema_str.c_str()).HasParseError()) {
        throw std::runtime_error(
            std::string("Invalid Schema: ") + rapidjson::GetParseError_En(schema_doc.GetParseError())
        );
    }

    // 3. Compile Schema
    rapidjson::SchemaDocument schema(schema_doc);
    rapidjson::SchemaValidator validator(schema);

    // 4. Validate
    if (!json.Accept(validator)) {
        // Se falhou, pegar erro detalhado
        rapidjson::StringBuffer sb;
        validator.GetInvalidSchemaPointer().StringifyUriFragment(sb);
        std::string schema_path = sb.GetString();

        std::string message = "JSON does not conform to schema.\n";
        message += "Invalid schema part: " + schema_path + "\n";
        message += "Keyword: " + std::string(validator.GetInvalidSchemaKeyword()) + "\n";

        throw std::runtime_error(message);
    }

    // Se passou, não faz nada
}

