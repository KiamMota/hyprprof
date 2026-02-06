#include "use_cases/show_things.hpp"
#include "hyprprof_path.hpp"
#include "utils/version.hpp"
#include "config_file.hpp"

const std::string use_cases::ShowThings::current_profile() noexcept
{
  return core::ConfigFile::get_current_profile_name(); 
}
const std::string use_cases::ShowThings::version() noexcept
{
  return app::version::VERSION;
}

const std::list<std::string> use_cases::ShowThings::list_profiles() noexcept 
{
  return core::HyprprofPath::profile_paths();
}
