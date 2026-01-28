#include "core/hyprprof_path.hpp"
#include "infra/fs/dir.hpp"
#include "infra/fs/dotconfig.hpp"
#include "infra/fs/file.hpp"

core::Hyprprof::Hyprprof() {
    _hyprprof_path = infra::fs::dotconfig::get_config_path() + "/hyprprof";
    _profile_list_path = infra::fs::dotconfig::get_config_path() + "/profile_list.json";
}

const std::string& core::Hyprprof::hyprprof_path() const noexcept { return _hyprprof_path; }
const std::string& core::Hyprprof::profile_list_path() const noexcept { return _profile_list_path; }

bool core::Hyprprof::path_exists() const noexcept
{
  return infra::fs::dir::exists(_hyprprof_path);
}

bool core::Hyprprof::profile_list_exists() const noexcept
{
  return infra::fs::file::exists(_profile_list_path);
}
