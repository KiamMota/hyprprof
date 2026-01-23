#ifndef JSON_HPP
#define JSON_HPP

#include <stdexcept>
#include <string>

namespace infra {
namespace json {

/**
 * @class JsonParseException
 * @brief Exception thrown when a JSON parsing error occurs.
 *
 * This class inherits from std::runtime_error and adds information
 * about the position of the error in the JSON, such as line and column.
 */
class JsonParseException : public std::runtime_error {
public:
    /**
     * @brief Constructor for the JSON parsing exception.
     * 
     * @param msg Detailed error message describing what went wrong.
     * @param line Line number in the JSON where the error occurred (1-based).
     * @param column Column number in the JSON where the error occurred (1-based).
     */
    JsonParseException(const std::string& msg, size_t line, size_t column)
        : std::runtime_error(msg), line_(line), column_(column) {}

    /**
     * @brief Gets the line number of the error.
     * 
     * @return Line number (1-based) where the error occurred.
     */
    size_t line() const { return line_; }

    /**
     * @brief Gets the column number of the error.
     * 
     * @return Column number (1-based) where the error occurred.
     */
    size_t column() const { return column_; }

private:
    size_t line_;   /**< Line in the JSON where the error occurred (1-based) */
    size_t column_; /**< Column in the JSON where the error occurred (1-based) */
};

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
