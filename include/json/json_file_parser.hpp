#ifndef JSON_FILE_PARSER_HPP
#define JSON_FILE_PARSER_HPP

#include <rapidjson/document.h>
#include <string>
namespace json {

class JsonFileParser {
private:
  std::string _json_file_str;
  std::string schema;

  rapidjson::Document d;
  rapidjson::Value environment;
  rapidjson::Value apps;

  bool _TryJsonParse();
  bool _HaveObject(const std::string &name);
  rapidjson::Value &_GetObject(const std::string &name);
  bool _ValidateSchema();
  bool _HaveAppsObject();
  bool _HaveEnvironmentObject();
  bool _HaveAppsTerminalObject();
  bool _HaveRequiredApps();

public:
  explicit JsonFileParser(const std::string &file_path);

  void Parse();
  std::string json_str() const;
};
} // namespace json

#endif
