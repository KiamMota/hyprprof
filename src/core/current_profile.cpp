#include "core/current_profile.hpp"

core::CurrentProfile::CurrentProfile(const std::string& profile_name, const std::string& profile_path)
{
  _current_profile_name = profile_name;
  _current_profile_path = profile_path;
}
