#ifndef JSON_FILE_PARSER_HPP
#define JSON_FILE_PARSER_HPP

#include "core/profile/profile.hpp"
#include "rapidjson/document.h"
#include <list>
#include <string>

namespace core {


class JsonManifest {
private:
  std::string _json_schema;
  std::string _json_str;
  rapidjson::Document doc;
public:
  JsonManifest(const std::string& json_str);
  bool parse();
  profile::Profile GetProfile();
  std::string profile_name();
  std::string version();
  std::string desciption();
  std::list<std::string> authors();
  std::string hyprland_version();
  std::string wayland_version();
};

} // namespace domain

#endif
