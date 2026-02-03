#ifndef JSON_FILE_PARSER_HPP
#define JSON_FILE_PARSER_HPP

#include "profile/profile.hpp"
#include "json/json_base.hpp"
#include <string>

namespace json {

class JSONManifestReader : public JSONBase {
  private:
    std::string _json_schema;
  public:
    JSONManifestReader();
    void set_json_string(const std::string& json_str);
    profile::Profile get_profile();
};
} // namespace json


#endif
