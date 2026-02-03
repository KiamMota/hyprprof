#ifndef JSON_BASE_HPP
#define JSON_BASE_HPP

#include "rapidjson/document.h"

#include <list>
#include <string>

namespace json {
class JSONBase {
  private:
    std::string _json_str;
    rapidjson::Document _document;
    const rapidjson::Value* _node = nullptr;
    JSONBase(const rapidjson::Value* node); 
  protected:
    JSONBase(const std::string& json_str);
    JSONBase() = default;
    void parse();
    const std::string& json_str() const noexcept;
  public:
    void set_json_string(const std::string& json_string);
    JSONBase get_in(const std::string& n) const;
    const std::string get_string(const std::string& n) const;
    const int get_int(const std::string& n) const;
    const bool get_bool(const std::string& n) const;
    const std::list<std::string> get_string_array(const std::string& n) const;
};

} // namespace json
  // namespace json

#endif // JSON_BASE_HPP
