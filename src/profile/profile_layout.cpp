#include "profile/profile_layout.hpp"
#include "infra/fs/dir.hpp"
#include "infra/fs/file.hpp"
#include "profile/profile_layout_exceptions.hpp"

profile::ProfileLayout::ProfileLayout()
{

}

void profile::ProfileLayout::set_path(const std::string& source_dir) {
    if (source_dir.empty())
    throw ProfileLayoutDirException("");
        _source_path = infra::fs::dir::get_absolute(source_dir);
    set_paths();
    check_paths();
}

void profile::ProfileLayout::set_paths() {
    _readme_path = _source_path + "/README.md";
    _manifest_path = _source_path + "/hyprprof.json";
    _assets_path = _source_path + "/assets";
    _config_path = _source_path + "/config";
    _extras_path = _config_path + "/extras";
    _scripts_path = _source_path + "/scripts";
}

void profile::ProfileLayout::check_paths() 
{
  using namespace infra::fs;
  if(!file::exists(_manifest_path))
    throw ProfileLayoutFileException("hyprprof.json");
  if(!dir::exists(_config_path))
    throw ProfileLayoutDirException("config");
}

bool profile::ProfileLayout::has_assets_path() const noexcept
{
  return infra::fs::dir::exists(_assets_path);
}

bool profile::ProfileLayout::has_readme_path() const noexcept
{
  return infra::fs::file::exists(_readme_path);
}

bool profile::ProfileLayout::has_extras_path() const noexcept
{
  return infra::fs::file::exists(_extras_path);
}

const std::string& profile::ProfileLayout::source_path() const noexcept {
    return _source_path;
}

const std::string& profile::ProfileLayout::manifest_path() const noexcept {
    return _manifest_path;
}

const std::string& profile::ProfileLayout::config_path() const noexcept {
    return _config_path;
}

const std::string& profile::ProfileLayout::readme_path() const noexcept {
    return _readme_path;
}

const std::string& profile::ProfileLayout::extras_path() const noexcept {
    return _extras_path;
}

const std::string& profile::ProfileLayout::assets_path() const noexcept {
    return _assets_path;
}

const std::string& profile::ProfileLayout::scripts_path() const noexcept {
    return _scripts_path;
}

