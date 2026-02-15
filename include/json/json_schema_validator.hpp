#ifndef JSON_SCHEMA_VALIDATOR_HPP
#define JSON_SCHEMA_VALIDATOR_HPP

#include <string>

namespace json {
class JSONSchemaValidator {
  public:
    static void validate_schema(const std::string& json, const std::string& schema);
};
} // namespace json

#endif // JSON_SCHEMA_VALIDATOR_HPP
