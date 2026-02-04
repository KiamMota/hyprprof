#include "hyprprof_path.hpp"
#include "fs/dir.hpp"
#include "fs/dotconfig.hpp"
#include "fs/file.hpp"
#include <stdexcept>

core::HyprprofPath::HyprprofPath() {
}

const std::string core::HyprprofPath::hyprprof_path() noexcept 
{
  return fs::dotconfig::get_config_path() + "/hyprprof";
}
const std::string core::HyprprofPath::config_path() noexcept 
{ 
  return fs::dotconfig::get_config_path() + "/hyprprof/config.json"; 
}

bool core::HyprprofPath::path_exists_in_hyprprof_path(const std::string& path) noexcept
{
  return fs::dir::exists(fs::dotconfig::get_config_path() + "/hyprprof/" + path);
}

bool core::HyprprofPath::has_config_file() noexcept
{
    return fs::file::exists(fs::dotconfig::get_config_path() + "/hyprprof/config.json");
}

void core::HyprprofPath::create_path(const std::string& name)
{
  if(fs::dir::exists(fs::dotconfig::get_config_path() + "/hyprprof/" + name))
    throw std::runtime_error("path named '" + name + "' already exists in ~/.config/hyprprof.");
  fs::dir::create(fs::dotconfig::get_config_path() + "/hyprprof/" + name);
}

const std::string core::HyprprofPath::get_path(const std::string &path) noexcept
{
  return fs::dotconfig::get_config_path() + "/hyprprof/" + path;
}
