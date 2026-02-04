#ifndef JSON_CONFIG_FILE_READER_HPP
#define JSON_CONFIG_FILE_READER_HPP

#include "rapidjson/document.h"
#include <string>
namespace json
{
class GlobalConfig {
private:
  rapidjson::Document _document;
  std::string _json_str;
  std::string _username;
  std::string _current_profile;
public:
    GlobalConfig();
    void set_json_context(const std::string& json_str);
    void remake_json();
    void create_json();
    const std::string& to_string() const;
    GlobalConfig& set_username(const std::string& username) ;
    GlobalConfig& set_current_profile(const std::string& curr) ;
    const std::string username() const noexcept;
    const std::string current_profile() const noexcept;
};

}
#endif // JSON_CONFIG_FILE_READER_HPP
