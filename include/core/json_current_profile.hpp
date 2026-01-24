#ifndef JSON_CURRENT_PROFILE_HPP
#define JSON_CURRENT_PROFILE_HPP

#include "core/current_profile.hpp"
#include <string>
namespace core
{
  class JsonCurrentProfile
  {
    private:
      std::string _profile_name;
      std::string _current_path;
    public:
      JsonCurrentProfile(const std::string& profile_name, const std::string& current_path);
      CurrentProfile get_current();
      const std::string get_json();
      std::string current_profile();
      std::string current_path();
  };
}
#endif // JSON_CURRENT_PROFILE_HPP
