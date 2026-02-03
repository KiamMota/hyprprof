#ifndef JSON_BASE_HPP
#define JSON_BASE_HPP

#include "rapidjson/document.h"

#include <string>

namespace json {
class JSONBase {
  private:
    std::string _json_str;
    rapidjson::Document _document;
    const rapidjson::Value* _node = nullptr;
  protected:
    JSONBase(const std::string& json_str);
    JSONBase() = default;
    void parse();
    const std::string& json_str() const noexcept;
    const rapidjson::Document& document() const;
  public:
    void set_json_string(const std::string& json_string);
};

} // namespace json
  // namespace json

#endif // JSON_BASE_HPP
