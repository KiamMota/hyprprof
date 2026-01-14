#ifndef JSON_FILE_PARSER_HPP
#define JSON_FILE_PARSER_HPP

#include <list>
#include <rapidjson/document.h>
#include <string>

namespace core {
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
  TypeError,
  EmptyOrNullValue
};

const char* JsonErrorToString(JsonFileParserError e);

class JsonFileParser {
private:
  std::string _json_file_str;
  std::string schema;
  std::list<std::string> _scripts;

  rapidjson::Document d;
  rapidjson::Value hyprprof;

  bool _TryJsonParse();
  bool _ValidateSchema();
  bool _HaveHyprprofObject();
  bool _HavePayload() const;
  
  JsonFileParserError _ValidateRunScripts() const;
  void _PopulateScripts();

  bool _HaveObject(const std::string& obj_name);
  rapidjson::Value& _GetObject(const std::string& obj_name); 
public:
  JsonFileParser();
  JsonFileParserError Parse(const std::string& json_str);
  bool hasPayload() const;
  std::list<std::string> scripts();
  std::string json_str() const;
  std::string profile_name() const;
  std::string version() const;
};

} // namespace install
} // namespace domain

#endif
