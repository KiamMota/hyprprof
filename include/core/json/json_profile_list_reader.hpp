#ifndef JSON_CURRENT_PROFILE_READER_HPP
#define JSON_CURRENT_PROFILE_READER_HPP

#include "rapidjson/document.h"
#include <string>
namespace core
{
namespace json
{
  class JSONProfileListReader
  {
  std::string _existing_json;
    rapidjson::Document doc;
    public:
      JSONProfileListReader(const std::string& json_src);
      const std::string current_profile_name() const noexcept;
        const std::string current_profile_path() const noexcept;
  };

}
}
#endif // JSON_CURRENT_PROFILE_READER_HPP
