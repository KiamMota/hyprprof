#include "infra/json.hpp"
#include "infra/fs/dir.hpp"
#include "infra/fs/file.hpp"
#include "infra/log.hpp"
#include "rapidjson/document.h"
#include "rapidjson/schema.h"
#include <fstream>
#include <stdexcept>

std::string infra::json::read_json_file(const std::string &file_path) {
    if(!infra::fs::dir::exists(file_path))
        throw std::runtime_error("File '" + file_path + "' does not exist");

    std::ifstream f(file_path);
    if(!f) 
        throw std::runtime_error("Failed to open '" + file_path + "'");

    std::stringstream buffer;
    buffer << f.rdbuf();
    auto content = buffer.str();
    if(content.empty())
        throw std::runtime_error("'" + file_path + "' is empty");

    return content;
}


bool infra::json::is_json_valid(const std::string& json) {

    rapidjson::Document doc;
    if (doc.Parse(json.c_str()).HasParseError()) {
        hypr_log::err("JSON parse error: ", rapidjson::GetParseError_En(doc.GetParseError()));
        return false;
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

