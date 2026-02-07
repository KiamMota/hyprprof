#include "fs/dir.hpp"
#include "fs/file.hpp"
#include "profile/profile_layout_exceptions.hpp"
#include <stdexcept>
#include "profile_layout_helper.hpp"


namespace profile {

ProfileLayoutHelper::ProfileLayoutHelper() {}

void ProfileLayoutHelper::check_required_paths(const std::string &path)
{
  std::string config = config_path(path);
  std::string mainfest_path = manifest_path(path);

  if(!hprof_fs::file::exists(mainfest_path))
      throw ProfileLayoutFileException("hyprprof.json");
  if(!hprof_fs::dir::exists(config))
      throw ProfileLayoutDirException("config");
}

bool ProfileLayoutHelper::has_dotfiles_path(const std::string& path) noexcept 
{ 
  return hprof_fs::dir::exists(hprof_fs::dir::get_absolute(path) + "/config/dotfiles"); 
}
bool ProfileLayoutHelper::has_hypr_path(const std::string& path) noexcept 
{ 
  return hprof_fs::dir::exists(hypr_path(path)); 
}
bool ProfileLayoutHelper::has_waybar_path(const std::string& path) noexcept 
{ 
  return hprof_fs::dir::exists(waybar_path(path)); 
}
bool ProfileLayoutHelper::has_readme_path(const std::string& path) noexcept { return false; }
bool ProfileLayoutHelper::has_assets_path(const std::string& path) noexcept { return false; }
bool ProfileLayoutHelper::has_assets_bg_path(const std::string& path) noexcept { return false; }
bool ProfileLayoutHelper::has_assets_fonts_path(const std::string& path) noexcept { return false; }

const std::string ProfileLayoutHelper::manifest_path(const std::string& path) noexcept 
{ 
  return hprof_fs::dir::get_absolute(path) + "/hyprprof.json"; 
}
const std::string ProfileLayoutHelper::config_path(const std::string& path) noexcept 
{ 
  return hprof_fs::dir::get_absolute(path) + "/config"; 
}
const std::string ProfileLayoutHelper::readme_path(const std::string& path) noexcept 
{ 
  return hprof_fs::dir::get_absolute(path) + "/README.md"; 
}
const std::string ProfileLayoutHelper::waybar_path(const std::string& path) noexcept 
{ 
  return hprof_fs::dir::get_absolute(path) + "/config/waybar"; 
}
const std::string ProfileLayoutHelper::hypr_path(const std::string& path) noexcept 
{ 
  return hprof_fs::dir::get_absolute(path) + "config/hypr"; 
}
const std::string ProfileLayoutHelper::dotfiles_path(const std::string& path) noexcept 
{ 
  return hprof_fs::dir::get_absolute(path) + "config/dotfiles"; 
}

const std::string ProfileLayoutHelper::concat_dotfile_path(const std::string &path, const std::string& name) noexcept
{
return hprof_fs::dir::get_absolute(path) + "/config/dotfiles/" + name;
}

bool ProfileLayoutHelper::has_this_dotfile(const std::string& path, const std::string &name) noexcept
{
  return hprof_fs::dir::exists(concat_dotfile_path(path, name)); 
}

const std::string ProfileLayoutHelper::manifest_content(const std::string &path)
{
  if(!hprof_fs::file::exists(manifest_path(path)))
    throw std::runtime_error("manifest file doesnt exists!");
  return hprof_fs::file::get_content(manifest_path(path));
}

const std::string ProfileLayoutHelper::assets_path(const std::string& path) noexcept { 
  return hprof_fs::dir::get_absolute(path) + "/assets"; 
}
const std::string ProfileLayoutHelper::assets_bg_path(const std::string& path) noexcept 
{ 
  return hprof_fs::dir::get_absolute(path) + "/assets/bg"; 
}
const std::string ProfileLayoutHelper::assets_fonts_path(const std::string& path) noexcept 
{ 
  return hprof_fs::dir::get_absolute(path) + "/assets/fonts"; 
}

} // namespace profile

