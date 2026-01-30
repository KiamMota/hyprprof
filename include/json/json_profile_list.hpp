#ifndef JSON_CURRENT_PROFILE_HPP
#define JSON_CURRENT_PROFILE_HPP

#include "current_profile.hpp"
#include "rapidjson/document.h"
#include <string>
namespace json {
class JSONProfileList {
  private:
    std::string _existing_json;
    std::string _profile_name;
    std::string _current_path;
    rapidjson::Document doc;
    void parse();

  public:
    JSONProfileList(const std::string& json_src);
    JSONProfileList();
    void set_existing_json(const std::string& json);
    core::CurrentProfile get_current();
    const std::string json_append(const std::string& current_profile,
                                const std::string& current_path);
    std::string current_profile();
    std::string current_path();
};
} // namespace json
#endif // JSON_CURRENT_PROFILE_HPP
