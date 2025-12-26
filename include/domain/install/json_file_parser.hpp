#ifndef JSON_FILE_PARSER_HPP
#define JSON_FILE_PARSER_HPP

#include <rapidjson/document.h>
#include <string>
namespace domain {
namespace install {

enum class JsonFileParserError
{
  NoError,
  PlaceHolder,
  NoSchema,
  ParsingError,
  EmptyJSON,
  JsonFileIsEmpty,
  NoHyprProfObject,
  NoAppsObject,
  NoTerminalObject,
};

const char* JsonErrorToString(JsonFileParserError e);

class JsonFileParser {
private:
  std::string _json_file_str;
  std::string schema;

  rapidjson::Document d;
  rapidjson::Value apps;
  rapidjson::Value hyprprof;

  bool _TryJsonParse();
  bool _ValidateSchema();
  bool _HaveHyprprofObject();
  bool _HaveAppsObject();
  bool _HaveRequiredApps();
  bool _HavePayload() const;
  bool _HaveObject(const std::string& obj_name);
  rapidjson::Value& _GetObject(const std::string& obj_name); 
public:
  JsonFileParser();
  JsonFileParserError Parse(const std::string& json_str);
  bool hasPayload() const;
  std::string json_str() const;
};

} // namespace install
} // namespace domain

#endif
