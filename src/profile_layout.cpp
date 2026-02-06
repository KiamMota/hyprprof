#include "fs/dir.hpp"
#include "fs/file.hpp"
#include "profile/profile_layout_exceptions.hpp"
#include "profile_layout.hpp"


namespace profile {

ProfileLayout::ProfileLayout() {}

void ProfileLayout::check_required_paths(const std::string &path)
{
  std::string config = config_path(path);
  std::string mainfest_path = manifest_path(path);

  if(!hprof_fs::file::exists(mainfest_path))
      throw ProfileLayoutFileException("hyrprof.json");
  if(!hprof_fs::dir::exists(config))
      throw ProfileLayoutDirException("config");
}

bool ProfileLayout::has_dotfiles_path(const std::string& path) noexcept 
{ 
  return hprof_fs::dir::exists(hprof_fs::dir::get_absolute(path) + "/config/dotfiles"); 
}
bool ProfileLayout::has_hypr_path(const std::string& path) noexcept 
{ 
  return false; 
}
bool ProfileLayout::has_waybar_path(const std::string& path) noexcept 
{ 
  return false; 
}
bool ProfileLayout::has_readme_path(const std::string& path) noexcept { return false; }
bool ProfileLayout::has_assets_path(const std::string& path) noexcept { return false; }
bool ProfileLayout::has_assets_bg_path(const std::string& path) noexcept { return false; }
bool ProfileLayout::has_assets_fonts_path(const std::string& path) noexcept { return false; }

const std::string ProfileLayout::manifest_path(const std::string& path) noexcept 
{ 
  return hprof_fs::dir::get_absolute(path) + "/hyprprof.json"; 
}
const std::string ProfileLayout::config_path(const std::string& path) noexcept 
{ 
  return hprof_fs::dir::get_absolute(path) + "/config"; 
}
const std::string ProfileLayout::readme_path(const std::string& path) noexcept 
{ 
  return hprof_fs::dir::get_absolute(path) + "/README.md"; 
}
const std::string ProfileLayout::waybar_path(const std::string& path) noexcept 
{ 
  return hprof_fs::dir::get_absolute(path) + "/config/waybar"; 
}
const std::string ProfileLayout::hypr_path(const std::string& path) noexcept 
{ 
  return hprof_fs::dir::get_absolute(path) + "config/hypr"; 
}
const std::string ProfileLayout::dotfiles_path(const std::string& path) noexcept 
{ 
  return hprof_fs::dir::get_absolute(path) + "config/dotfiles"; 
}

const std::string ProfileLayout::concat_dotfile_path(const std::string &path, const std::string& name) noexcept
{
return hprof_fs::dir::get_absolute(path) + "/config/dotfiles/" + name;
}

bool ProfileLayout::has_this_dotfile(const std::string& path, const std::string &name) noexcept
{
  return hprof_fs::dir::exists(concat_dotfile_path(path, name)); 
}

const std::string ProfileLayout::manifest_content(const std::string &path)
{
  return hprof_fs::file::get_content(manifest_path(path));
}

const std::string ProfileLayout::assets_path(const std::string& path) noexcept { 
  return hprof_fs::dir::get_absolute(path) + "/assets"; 
}
const std::string ProfileLayout::assets_bg_path(const std::string& path) noexcept 
{ 
  return hprof_fs::dir::get_absolute(path) + "/assets/bg"; 
}
const std::string ProfileLayout::assets_fonts_path(const std::string& path) noexcept 
{ 
  return hprof_fs::dir::get_absolute(path) + "/assets/fonts"; 
}

} // namespace profile

