#ifndef JSON_BASE_HPP
#define JSON_BASE_HPP

#include "rapidjson/document.h"

#include <list>
#include <string>

namespace json {
class JsonBase {
  private:
    std::string _json_str;
    rapidjson::Document _document;
  protected:
    JsonBase(const std::string& json_str);
    void parse();
    const std::string& json_str() const noexcept;
  public:
    const std::string get_string(const std::string& n) const;
    const int get_int(const std::string& n) const;
    const bool get_bool(const std::string& n) const;
    const std::list<std::string> get_string_array(const std::string& n) const;
};

} // namespace json
  // namespace json

#endif // JSON_BASE_HPP
