#ifndef JSON_HPP
#define JSON_HPP

#include <string>

namespace infra {
namespace json {

std::string read_json_file(const std::string& json_file);
/**
 * @brief Validates a JSON string against a JSON Schema.
 *
 * This function takes a JSON string and a JSON Schema string containing
 * the validation rules. It returns `true` if the JSON complies with
 * the schema, or `false` otherwise.
 *
 * @note The function internally uses `try`/`catch`. Any exceptions
 * thrown during validation are caught, and the main program execution
 * continues normally without interruption.
 *
 * @param json The JSON string to be validated.
 * @param json_schema The JSON Schema string defining the rules.
 *
 * @return `true` if the JSON is valid, `false` otherwise.
 */
bool validate_schema(const std::string& json, const std::string& json_schema);

/**
 * @brief Parses a JSON string or file.
 *
 * This function can parse a JSON provided either as a string or from a file.
 * If the JSON contains any errors, it will throw an exception.
 *
 * @param json The JSON content to parse, either as a string or a file path.
 *
 * @return `true` if parsing succeeds.
 *
 * @throws std::exception Thrown if the JSON is invalid or cannot be parsed.
 */
bool is_json_valid(const std::string& json);

} // namespace json
} // namespace infra

#endif
