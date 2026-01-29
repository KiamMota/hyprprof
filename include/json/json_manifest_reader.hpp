#ifndef JSON_FILE_PARSER_HPP
#define JSON_FILE_PARSER_HPP

#include "profile/profile.hpp"
#include "rapidjson/document.h"
#include <list>
#include <string>

namespace json {

class JSONManifestReader {
  private:
    std::string _json_schema;
    std::string _json_str;
    rapidjson::Document doc;

  public:
    JSONManifestReader();
    void set_json_str(const std::string& json_str);
    bool parse();
    profile::Profile get_profile();
    std::string profile_name();
    std::string version();
    std::string desciption();
    std::list<std::string> authors();
    std::string hyprland_version();
    std::string wayland_version();
};
} // namespace json


#endif
