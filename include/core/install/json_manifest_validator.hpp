#ifndef JSON_FILE_PARSER_HPP
#define JSON_FILE_PARSER_HPP

#include "rapidjson/document.h"
#include <string>

namespace core {
namespace install {


class JsonManifestValidator {
private:
  std::string _json_schema;
public:
  JsonManifestValidator();
  void Parse(const std::string& json_str);
};

} // namespace install
} // namespace domain

#endif
