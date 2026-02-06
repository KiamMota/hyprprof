#ifndef JSON_FILE_PARSER_HPP
#define JSON_FILE_PARSER_HPP

#include "dotfile.hpp"
#include "profile/profile_model.hpp"
#include "rapidjson/document.h"
#include <list>
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
    const profile::Profile get_profile();
    const std::list<core::DotFile> get_dotconfigs();
    
};
} // namespace json


#endif
