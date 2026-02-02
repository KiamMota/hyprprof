#include "profile/profile_layout.hpp"
#include "infra/fs/dir.hpp"
#include "infra/fs/file.hpp"
#include "profile/profile_layout_exceptions.hpp"
#include <list>
#include <stdexcept>
#include <string>

profile::ProfileLayout::ProfileLayout() {}

void profile::ProfileLayout::set_path(const std::string& source_dir) {
    if (source_dir.empty())
        throw ProfileLayoutDirException("dir is empty");
    _source_path = infra::fs::dir::get_absolute(source_dir);
    set_paths();
    check_paths();
}

void profile::ProfileLayout::move_profile_to(const std::string& new_src) {
    std::string new_src_abs = infra::fs::dir::get_absolute(new_src);

    if (!infra::fs::dir::is_emp(new_src_abs))
        throw std::runtime_error(new_src + " is not empty!");

    if (!infra::fs::dir::copy(_source_path, new_src_abs))
        throw std::runtime_error("cannot copy profile to " + new_src_abs);

    infra::fs::dir::remove(_source_path);

    _source_path = new_src_abs;
    set_paths();
    check_paths();
}


void profile::ProfileLayout::set_paths() {
    _readme_path = _source_path + "/README.md";
    _manifest_path = _source_path + "/hyprprof.json";
    _config_path = _source_path + "/config";
    _dotfiles_path = _source_path + "/dotfiles";
    _hypr_path = _config_path + "/hypr";
    _waybar_path = _config_path + "/waybar";
}

void profile::ProfileLayout::check_paths() {
    using namespace infra::fs;
    if (!file::exists(_manifest_path))
        throw ProfileLayoutFileException("hyprprof.json");
    if (!dir::exists(_config_path))
        throw ProfileLayoutDirException("config");
}


bool profile::ProfileLayout::has_readme_path() const noexcept {
    return infra::fs::file::exists(_readme_path);
}

bool profile::ProfileLayout::has_waybar_path() const noexcept {
    return infra::fs::dir::exists(_waybar_path);
}

bool profile::ProfileLayout::has_dotfiles_path() const noexcept
{
  return infra::fs::dir::exists(_dotfiles_path);
}

const std::string& profile::ProfileLayout::source_path() const noexcept { return _source_path; }

const std::string& profile::ProfileLayout::manifest_path() const noexcept { return _manifest_path; }

const std::string& profile::ProfileLayout::config_path() const noexcept { return _config_path; }

const std::string& profile::ProfileLayout::readme_path() const noexcept { return _readme_path; }


const std::string& profile::ProfileLayout::waybar_path() const noexcept { return _waybar_path; }


bool profile::ProfileLayout::has_hypr_path() const noexcept {
    return infra::fs::dir::exists(_hypr_path);
}

bool profile::ProfileLayout::has_assets_path() const noexcept {
    return infra::fs::dir::exists(_assets_path);
}

bool profile::ProfileLayout::has_assets_bg_path() const noexcept {
    return infra::fs::dir::exists(_assets_bg_path);
}

bool profile::ProfileLayout::has_assets_fonts_path() const noexcept {
    return infra::fs::dir::exists(_assets_fonts_path);
}

const std::string& profile::ProfileLayout::hypr_path() const noexcept {
    return _hypr_path;
}

const std::string& profile::ProfileLayout::dotfiles_path() const noexcept {
    return _dotfiles_path;
}

const std::string& profile::ProfileLayout::assets_path() const noexcept {
    return _assets_path;
}

const std::string& profile::ProfileLayout::assets_bg_path() const noexcept {
    return _assets_bg_path;
}

const std::string& profile::ProfileLayout::assets_fonts_path() const noexcept {
    return _assets_fonts_path;
}

