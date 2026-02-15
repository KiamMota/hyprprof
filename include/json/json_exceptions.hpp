#ifndef JSON_EXCEPTIONS_HPP
#define JSON_EXCEPTIONS_HPP

#include <stdexcept>
#include <string>
namespace json {

class JsonEmptyException : public std::runtime_error {
  public:
    JsonEmptyException() : std::runtime_error("JSON Document is empty.") {}
};

class JsonParseException : public std::runtime_error {
  public:
    JsonParseException(const std::string& msg, size_t line, size_t column)
        : std::runtime_error(msg), line_(line), column_(column) {}

    size_t line() const { return line_; }

    size_t column() const { return column_; }

  private:
    size_t line_;   /**< Line in the JSON where the error occurred (1-based) */
    size_t column_; /**< Column in the JSON where the error occurred (1-based) */
};

class JsonSearchTypeException : public std::runtime_error {
  public:
    JsonSearchTypeException(const char* field_to_search, const char* found_type,
                            const char* expected_type)
        : std::runtime_error(std::string("Field '") + (field_to_search ? field_to_search : "null") +
                             "' expected type '" + (expected_type ? expected_type : "null") +
                             "', but got '" + (found_type ? found_type : "null") + "'") {}
};

class JsonSearchFieldNotFoundException : public std::runtime_error {
  public:
    JsonSearchFieldNotFoundException(const char* field)
        : std::runtime_error("field named '" + std::string(field) +
                             "' not found in JSON Document.") {}
};

} // namespace json

#endif // JSON_EXCEPTIONS_HPP
