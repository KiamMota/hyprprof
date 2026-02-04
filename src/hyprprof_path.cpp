#include "hyprprof_path.hpp"
#include "fs/dir.hpp"
#include "fs/dotconfig.hpp"
#include "fs/file.hpp"
#include <stdexcept>

core::HyprprofPath::HyprprofPath() {
    _hyprprof_path = fs::dotconfig::get_config_path() + "/hyprprof";
    _config_path = fs::dotconfig::get_config_path() + "/config.json";
}

const std::string& core::HyprprofPath::hyprprof_path() const noexcept { return _hyprprof_path; }
const std::string& core::HyprprofPath::config_path() const noexcept { return _config_path; }

bool core::HyprprofPath::path_exists() const noexcept
{
  return fs::dir::exists(_hyprprof_path);
}

bool core::HyprprofPath::has_config_file() const noexcept
{
    return fs::file::exists(_config_path);
}

bool core::HyprprofPath::profile_path_exists(const std::string& prof) const noexcept
{
  return fs::dir::exists(_hyprprof_path + "/" + prof);
}

void core::HyprprofPath::create_path(const std::string& name)
{
  if(fs::dir::exists(_hyprprof_path + "/" + name))
    throw std::runtime_error("path named '" + name + "' already exists in ~/.config/hyprprof.");
  fs::dir::create(_hyprprof_path + "/" + name);
}

const std::string core::HyprprofPath::profile_path(const std::string& path) const 
{
    return _hyprprof_path + "/" + path;
}


void core::HyprprofPath::create_config_file()
{
  fs::file::create(_hyprprof_path + "/config.json");
}
