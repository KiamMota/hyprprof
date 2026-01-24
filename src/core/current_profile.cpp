#include "core/current_profile.hpp"

core::CurrentProfile::CurrentProfile()
{
}

void core::CurrentProfile::set_current_path(const std::string& path)
{
  _current_profile_path = path;
}
void core::CurrentProfile::set_profile_name(const std::string& name)
{
  _current_profile_name = name;
}
