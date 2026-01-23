#ifndef JSON_FILE_PARSER_HPP
#define JSON_FILE_PARSER_HPP

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
  void parse();
  std::string profile_name();
  std::string version();
  std::string desciption();
  std::list<std::string> authors();

};

} // namespace domain

#endif
