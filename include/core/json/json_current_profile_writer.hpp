#ifndef JSON_CURRENT_PROFILE_HPP
#define JSON_CURRENT_PROFILE_HPP

#include "core/current_profile.hpp"
#include "rapidjson/document.h"
#include <string>
namespace core

{
namespace json {
class JSONCurrentProfileWriter {
  private:
    std::string _json_src;
    std::string _profile_name;
    std::string _current_path;
    rapidjson::Document doc;

  public:
    JSONCurrentProfileWriter(const std::string& json_src);
    JSONCurrentProfileWriter();
    void parse();
    CurrentProfile get_current();
    const std::string make_json(const std::string& current_profile,
                                const std::string& current_path);
    std::string current_profile();
    std::string current_path();
};
} // namespace json
} // namespace core
#endif // JSON_CURRENT_PROFILE_HPP
