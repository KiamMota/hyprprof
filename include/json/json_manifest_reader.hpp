#ifndef JSON_FILE_PARSER_HPP
#define JSON_FILE_PARSER_HPP

#include "profile/profile.hpp"
#include "rapidjson/document.h"
#include <string>

namespace json {

class JSONManifestReader {
  private:
    rapidjson::Document _document;
    std::string _json_str;
    std::string _json_schema;
  public:
    JSONManifestReader();
    void run(const std::string& json_str);
    profile::Profile get_profile();
};
} // namespace json


#endif
